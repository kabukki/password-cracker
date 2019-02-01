#include <iostream>
#include "AttackBruteforce.hpp"

AttackBruteforce::AttackBruteforce()
	: _name("Bruteforce"), _logger(Logger(std::cout))
{}
AttackBruteforce::~AttackBruteforce () {}

IAttack::results	AttackBruteforce::crack(const Hash::md5digest &digest)
{
	IAttack::results results { false, nullptr, 0 };

	return results;
}

const std::string&	AttackBruteforce::name()
{
	return _name;
}
