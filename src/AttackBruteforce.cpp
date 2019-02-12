#include <algorithm>
#include <iostream>
#include <atomic>
#include <vector>
#include <cmath>
#include <omp.h>
#include "AttackBruteforce.hpp"
#include "Color.hpp"

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
std::string			AttackBruteforce::nthString(const size_t n) const
{
	std::string		password;
	size_t			offset = _possibilities;

	// Avoid automatic reallocation
	password.reserve(_maxLength);

	for (size_t x = _maxLength; x > 0; --x) {
		offset -= _pow.at(x);

		if (n >= offset) {
			password += _charset[((n - offset) / _pow.at(x - 1)) % _charsetLength];
		}
	}

	return password;
}

void					AttackBruteforce::crack(std::vector<IAttack::pair>& list) const
{
	std::atomic<bool>	done(false);
	size_t				nbCrackedBefore = std::count_if(list.begin(), list.end(), [](IAttack::pair& pair) { return pair.isCracked(); });

	_logger.log(description());
	_logger.log(std::to_string(_possibilities) + " possibilities total");
	_logger.log("Using " + std::to_string(NUM_THREADS) + " threads");

	#pragma omp parallel shared(list) num_threads(NUM_THREADS)
	{
		size_t start = omp_get_thread_num();
		size_t step = omp_get_num_threads();

		for (size_t n = start; !done && n < _possibilities; n += step) {
			std::string password = nthString(n);
			
			for (auto& pair : list) {
				if (pair.digest->check(password)) {
					pair.password = std::make_unique<std::string>(password);
					// _logger << Logger::SUCCESS << "Found " << *(pair.digest) << " : " << Color::BOLD << password << Color::RESET << std::endl;
					// If all digests have been cracked, end here.
					if (std::all_of(list.begin(), list.end(), [](IAttack::pair& pair) { return pair.isCracked(); })) {
						done = true;
						break;
					}
				}
			}
		}	
	}

	if (std::count_if(list.begin(), list.end(), [](IAttack::pair& pair) { return pair.isCracked(); }) - nbCrackedBefore == 0) {
		_logger.warn("Did not find any password");
	}
}

const std::string&	AttackBruteforce::name() const
{
	return _name;
}

const std::string	AttackBruteforce::description() const
{
	return "Max length is " + std::to_string(_maxLength) + " with the following charset: " + _charset;
}
