#include <iostream>
#include "AttackBruteforce.hpp"

AttackBruteforce::AttackBruteforce()
	: _name("Bruteforce"), _logger(Logger(std::cout))
{}
AttackBruteforce::~AttackBruteforce () {}

std::string&	AttackBruteforce::crack(const std::string &digest)
{

}

const std::string&	AttackBruteforce::name()
{
	return _name;
}
