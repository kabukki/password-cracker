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

void					AttackBruteforce::crack(const std::vector<HashMD5> digests, std::vector<IAttack::results>& results)
{
	std::atomic<bool>	done(false);
	size_t				resultsSizeBefore = results.size();

	_logger.log(description());
	_logger.log(std::to_string(_possibilities) + " possibilities total");
	_logger.log("Using " + std::to_string(NUM_THREADS) + " threads");

	#pragma omp parallel shared(results) num_threads(NUM_THREADS)
	{
		size_t start = omp_get_thread_num();
		size_t step = omp_get_num_threads();

		for (size_t n = start; !done && n < _possibilities; n += step) {
			std::string password = nthString(n);
			
			for (auto& digest : digests) {
				// std::cout << digest << std::endl;
				if (digest.check(password)) {
					_logger.success("Found " + password);
					results.push_back(IAttack::results {
						std::make_unique<HashMD5>(digest),
						std::make_unique<std::string>(password)
					});
				}
				if (results.size() == digests.size()) {
					done = true;
					break;
				}
			}
		}	
	}

	if (results.size() - resultsSizeBefore == 0) {
		_logger.warn("Did not find any password");
	}
}

const std::string&	AttackBruteforce::name()
{
	return _name;
}

const std::string	AttackBruteforce::description()
{
	return "Max length is " + std::to_string(_maxLength) + " with the following charset: " + _charset;
}
