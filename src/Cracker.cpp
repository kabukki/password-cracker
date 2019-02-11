#include <algorithm>
#include <iostream>
#include <memory>
#include <iterator>
#include <chrono>
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

/**
 * Crack a list of <digest, password> pair list
 * Returns true if any of the digests have been cracked
 */
bool								Cracker::crack(std::vector<IAttack::pair>& list)
{
	auto							begin = std::chrono::steady_clock::now();

	if (_strategy.empty()) {
		_logger.warn("No strategy specified to crack password. Aborting");
		return false;
	} else if (list.empty()) {
		_logger.warn("No digest to crack. Aborting");
		return false;
	}
	
	_logger << Logger::NEUTRAL << "Attempting to crack " << Color::FG_YELLOW << list.size() << Color::RESET << " digests." << std::endl;
	_logger << Logger::NEUTRAL << "Strategy is to use: " << strategyToString() << "." << std::endl;

	for (auto& attack : _strategy) {
		_logger << Logger::NEUTRAL << "Using attack: " << Color::FG_YELLOW << attack->name() << Color::RESET << std::endl;
		attack->crack(list);

		// All digests have been cracked
		if (std::all_of(list.begin(), list.end(), [](IAttack::pair& pair) { return pair.isCracked(); })) {
			break;
		}
	}

	_logger << Logger::NEUTRAL
		<< "Found " << std::count_if(list.begin(), list.end(), [](IAttack::pair& pair) { return pair.isCracked(); })
		<< "/" << list.size() << " passwords" << std::endl;
	
	for (auto& pair : list) {
		if (pair.isCracked()) {
			_logger << Logger::SUCCESS << *(pair.digest) << " : " << Color::BOLD << *(pair.password) << Color::RESET << std::endl;
		} else {
			_logger << Logger::ERROR << *(pair.digest) << " : Not found" << Color::RESET << std::endl;
		}
	}

	_logger.log("Elapsed time: " + std::to_string(
		std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count()
	) + "ms");

	return std::any_of(list.begin(), list.end(), [](IAttack::pair& pair) { return pair.isCracked(); });
}

void	Cracker::addAttack(std::shared_ptr<IAttack> attack)
{
	_strategy.push_back(attack);
}
