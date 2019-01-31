#include <iostream>
#include "AttackDictionary.hpp"
#include "Cracker.hpp"
#include "Color.hpp"

Cracker::Cracker() {}
Cracker::~Cracker() {}

std::string&	Cracker::crack(const std::string &digest)
{
	_attack = new AttackDictionary();
	std::cout << "Attempting to crack digest using strategy: " << Color::BOLD << Color::FG_YELLOW << _attack->name() << Color::RESET << std::endl;
	_attack->crack(digest);
}
