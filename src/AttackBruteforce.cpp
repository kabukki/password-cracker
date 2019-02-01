#include <iostream>
#include "AttackBruteforce.hpp"

AttackBruteforce::AttackBruteforce()
	: _name("Bruteforce"), _logger(Logger(std::cout)), _characterSet("abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*"), _maxLength(8)
{}
AttackBruteforce::~AttackBruteforce () {}

IAttack::results	AttackBruteforce::crack(const Hash::md5digest &digest)
{
	IAttack::results results { false, nullptr, 0 };

	for (unsigned int i = 0; i < _maxLength; i++) {
		for (char c : _characterSet) {
			std::cout << c << std::endl;
		}
	}
	return results;
}

const std::string&	AttackBruteforce::name()
{
	return _name;
}
