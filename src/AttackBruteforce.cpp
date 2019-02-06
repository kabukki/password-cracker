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

/**
 * Bruteforce every combination in a given section.
 * A section starts with
 * 		start - first - first
 * and ends with
 * 		start - last - last
 * For example, if the character set is 'abcd' and the start letter is 'a',
 * this function will go through 'aaa' to 'add'
 */
IAttack::results	AttackBruteforce::crackSection(const Hash::md5digest &digest, const size_t length, size_t startCharacterIndex)
{
	unsigned int				setLength = static_cast<int>(_characterSet.length());
	unsigned long long			combinations = std::pow(setLength, length - 1);
	IAttack::results			results { false, nullptr, 0 };
	std::string					password(length, _characterSet.front());
	std::vector<size_t>			indices(length, 0);

	indices[0] = startCharacterIndex;
	password[0] = _characterSet[indices[0]];

	for (unsigned long long x = 0; x < combinations; x++) {

		results.attempts++;
		// std::cout << password << "\n";

		if (Hash::check(password, digest)) {
			results.success = true;
			results.password = std::make_unique<std::string>(password);
			break;
		}

		// Generate next string
		for (int n = length - 1; n > 0; n--) {
			indices[n]++;
			password[n] = _characterSet[indices[n]];
			// If the penultimate letter wrapped, then all possbilities have been checked for this section
			// So we don't reset this letter and the loop will end here.
			if (indices[n] >= setLength && n > 1) {
				indices[n] = 0;
				password[n] = _characterSet[indices[n]];
			} else {
				break;
			}
		}
	}
	return results;
}

IAttack::results	AttackBruteforce::crack(const Hash::md5digest &digest, const size_t length)
{
	IAttack::results			results { false, nullptr, 0 };

	for (size_t startCharacterIndex = 0; startCharacterIndex < _characterSet.length(); startCharacterIndex++) {
		_logger << Logger::NEUTRAL << "Trying combinations starting with " << _characterSet[startCharacterIndex] << std::endl;
		results = crackSection(digest, length, startCharacterIndex);
		if (results.success) {
			break;
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
