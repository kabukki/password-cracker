#include <iostream>
#include <algorithm>
#include "Cracker.hpp"
#include "Color.hpp"

Cracker::Cracker() : _logger(Logger(std::cout)) {}
Cracker::~Cracker() {}

std::string	Cracker::strategyToString() const
{
	std::string strategy;
	std::string comma = "";

	for (auto attack : _strategy) {
		strategy += comma + attack->name();
		comma = ", then ";
	}
	return strategy;
}

void	Cracker::crack(const Hash::md5digest &digest)
{
	if (_strategy.empty()) {
		_logger.warn("No strategy specified to crack password. Aborting");
		return;
	}
	
	std::cout
		<< "Attempting to crack digest: " << Color::FG_YELLOW << digest << Color::RESET << ". "
		<< "Strategy is to use: " << strategyToString() << "." << std::endl;

	for (auto& attack : _strategy) {
		IAttack::results results;

		std::cout << "Using attack: " << Color::BOLD << Color::FG_YELLOW << attack->name() << Color::RESET << std::endl;
		results = attack->crack(digest);
		if (results.success == true) {
			_logger.success("Found password " + *(results.password) + " after " + std::to_string(results.attempts) + " attempts");
			return;
		} else {
			_logger.warn("Could not find password using " + attack->name() + " attack.");
		}
	}
	_logger.error("Unable to crack digest.");
}

void	Cracker::addAttack(std::shared_ptr<IAttack> attack)
{
	_strategy.push_back(attack);
}
