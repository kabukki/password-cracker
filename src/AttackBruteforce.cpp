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

IAttack::results		AttackBruteforce::crack(const HashMD5& digest)
{
	IAttack::results	results { false, nullptr, std::chrono::milliseconds(0) };
	std::atomic<bool>	done(false);
	auto				begin = std::chrono::steady_clock::now();

	// results.digest = &digest;

	_logger.log(description());
	_logger.log(std::to_string(_possibilities) + " possibilities total");
	_logger.log("Using " + std::to_string(NUM_THREADS) + " threads");

	#pragma omp parallel shared(results) num_threads(NUM_THREADS)
	{
		size_t start = omp_get_thread_num();
		size_t step = omp_get_num_threads();

		for (size_t n = start; !done && n < _possibilities; n += step) {
			std::string password = nthString(n);
			
			if (digest.check(password)) {
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

const std::string	AttackBruteforce::description()
{
	return "Max length is " + std::to_string(_maxLength) + " with the following charset: " + _charset;
}
