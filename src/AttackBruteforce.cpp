#include <iostream>
#include <atomic>
#include <vector>
#include <cmath>
#include <omp.h>
#include "AttackBruteforce.hpp"

AttackBruteforce::AttackBruteforce(const std::string &charset, const size_t maxLength)
	: _name("Bruteforce"), _logger(Logger(std::cout, "bruteforce")), _charset(charset), _charsetLength(charset.length()), _maxLength(maxLength)
{}
AttackBruteforce::~AttackBruteforce () {}

/**
 * TODO optimize
 */
std::string			AttackBruteforce::nthString(const size_t n)
{
	std::string password;
	size_t offset = 0;

	for (size_t x = 0; n >= offset; ++x) {
		size_t power = std::pow(_charsetLength, x);

		if (x > 0) {
			offset += power;
		}
		
		if (n >= offset) {
			password.insert(0, 1, _charset[((n - offset) / power) % _charsetLength]);
		}
	}

	return password;
}

IAttack::results		AttackBruteforce::crack(const Hash::md5digest &digest)
{
	IAttack::results	results { false, nullptr, 0, std::chrono::milliseconds(0) };
	std::atomic<bool>	done(false);
	size_t				possibilities = 0;
	auto				begin = std::chrono::steady_clock::now();
	
	for (size_t n = 1; n <= _maxLength; ++n) {
		possibilities += std::pow(_charsetLength, n);
	}

	_logger.log(describe());
	_logger.log(std::to_string(possibilities) + " possibilities");
	_logger.log("Using " + std::to_string(NUM_THREADS) + " threads");

	#pragma omp parallel shared(results) num_threads(NUM_THREADS)
	{
		size_t start = possibilities * omp_get_thread_num() / omp_get_num_threads();
		size_t end = possibilities * (omp_get_thread_num() + 1) / omp_get_num_threads();

		for (size_t n = start; !done && n < end; ++n) {
			std::string password = nthString(n);
			
			results.attempts++;

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
