#include <iostream>
#include <atomic>
#include <vector>
#include <cmath>
#include <omp.h>
#include "AttackBruteforce.hpp"

AttackBruteforce::AttackBruteforce(const std::string &charset, const size_t maxLength)
	: _name("Bruteforce"), _logger(Logger(std::cout, "bruteforce")), _charset(charset), _charsetLength(charset.length()), _maxLength(maxLength), _possibilities(0)
{
	// Store useful powers
	for (size_t n = 0; n <= _maxLength; ++n) {
		_pow[n] = std::pow(_charsetLength, n);
		if (n > 0) {
			_possibilities += _pow[n];
		}
	}
}
AttackBruteforce::~AttackBruteforce () {}

/**
 * Returns the nth bruteforce string
 */
std::string			AttackBruteforce::nthString(const size_t n)
{
	std::string		password;
	size_t			offset = _possibilities;

	// Avoid automatic reallocation
	password.reserve(_maxLength);

	for (size_t x = _maxLength; x > 0; --x) {
		offset -= _pow[x];

		if (n >= offset) {
			password += _charset[((n - offset) / _pow[x - 1]) % _charsetLength];
		}
	}

	return password;
}

IAttack::results		AttackBruteforce::crack(const Hash::md5digest &digest)
{
	IAttack::results	results { false, nullptr, 0, std::chrono::milliseconds(0) };
	std::atomic<bool>	done(false);
	auto				begin = std::chrono::steady_clock::now();

	_logger.log(describe());
	_logger.log(std::to_string(_possibilities) + " possibilities total");
	_logger.log("Using " + std::to_string(NUM_THREADS) + " threads");

	#pragma omp parallel shared(results) num_threads(NUM_THREADS)
	{
		size_t start = _possibilities * omp_get_thread_num() / omp_get_num_threads();
		size_t end = _possibilities * (omp_get_thread_num() + 1) / omp_get_num_threads();

		for (size_t n = start; !done && n < end; ++n) {
			std::string password = nthString(n);
			
			++results.attempts;

			// #pragma omp master
			// if (results.attempts > 0 && results.attempts % 10000000 == 0) {
			// 	_logger.log(std::to_string(results.attempts / 10000000) + " millionth attempt");
			// }
			
			if (Hash::check(password, digest)) {
				done = true;
				results.success = true;
				results.password = std::make_unique<std::string>(password);
			}
		}	
	}
	
	results.duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin);

	if (results.success) {
		_logger.success("Found");
	} else {
		_logger.error("Not found");
	}

	return results;
}

const std::string&	AttackBruteforce::name()
{
	return _name;
}

const std::string	AttackBruteforce::describe()
{
	return "Max length is " + std::to_string(_maxLength) + " with the following charset: " + _charset;
}
