#include <iostream>
#include <cmath>
#include <omp.h>
#include <atomic>
#include "Cracker.hpp"
#include "Color.hpp"

Cracker::Cracker() : _logger(Logger(std::cout, "cracker")) {}
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

bool	Cracker::crack(const Hash::md5digest &digest)
{
	if (_strategy.empty()) {
		_logger.warn("No strategy specified to crack password. Aborting");
		return false;
	}
	
	_logger << Logger::NEUTRAL << "Attempting to crack digest: " << Color::FG_YELLOW << digest << Color::RESET << std::endl;
	_logger << Logger::NEUTRAL << "Strategy is to use: " << strategyToString() << "." << std::endl;

	for (auto& attack : _strategy) {
		IAttack::results results;

		_logger << Logger::NEUTRAL << "Using attack: " << Color::FG_YELLOW << attack->name() << Color::RESET << std::endl;
		results = attack->crack(digest);

		if (results.success == true) {
			_logger << Logger::SUCCESS
				<< "Found password " << Color::BOLD << *(results.password) << Color::RESET
				<< " in " << results.duration.count() << "ms"
				<< " after " << results.attempts << " attempts" << std::endl;
			return true;
		} else {
			_logger.warn("Could not find password using " + attack->name() + " attack.");
		}
	}
	_logger.error("Unable to crack digest.");
	return false;
}

void	Cracker::addAttack(std::shared_ptr<IAttack> attack)
{
	_strategy.push_back(attack);
}
