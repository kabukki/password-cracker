#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>
#include "AttackBruteforce.hpp"

AttackBruteforce::AttackBruteforce(const std::string &characterSet, const unsigned int maxLength)
	: _name("Bruteforce"), _logger(Logger(std::cout, "bruteforce")), _characterSet(characterSet), _maxLength(maxLength)
{}
AttackBruteforce::~AttackBruteforce () {}

IAttack::results	AttackBruteforce::crack(const Hash::md5digest &digest, const size_t length)
{
	unsigned int				setLength = static_cast<int>(_characterSet.length());
	unsigned int				combinations = std::pow(setLength, length);
	IAttack::results			results { false, nullptr, 0 };
	std::string					password(length, 0);
	std::vector<unsigned int>	indices(length, 0);

	for (unsigned int x = 0; x < combinations; x++) {
		std::transform(
			indices.begin(), indices.end(), password.begin(),
			[this](int index) -> char { return _characterSet[index]; }
		);

		results.attempts++;

		if (Hash::check(password, digest)) {
			results.success = true;
			results.password = std::make_unique<std::string>(password);
			break;
		}

		// Generate next string
		for (int n = length - 1; n >= 0; n--) {
			indices[n]++;
			// If the first letter wrapped, then all possbilities have been checked
			// So we don't reset this letter and the loop will end here.
			if (indices[n] >= setLength && n > 0) {
				indices[n] = 0;
			} else {
				break;
			}
		}
	}
	return results;
}

IAttack::results	AttackBruteforce::crack(const Hash::md5digest &digest)
{
	IAttack::results results;

	for (size_t n = 1; n <= _maxLength; n++) {
		_logger << Logger::NEUTRAL << "Trying with length: " << n << std::endl;
		results = crack(digest, n);
		if (results.success) {
			break;
		}
	}
	
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

void				AttackBruteforce::describe()
{
	_logger << Logger::NEUTRAL << "Max length is " << _maxLength << " with the following charset: " << _characterSet << std::endl;
}
