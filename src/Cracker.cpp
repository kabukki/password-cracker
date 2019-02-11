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

bool								Cracker::crack(const std::vector<HashMD5> digests)
{
	auto							begin = std::chrono::steady_clock::now();
	std::vector<IAttack::results>	results;

	if (_strategy.empty()) {
		_logger.warn("No strategy specified to crack password. Aborting");
		return false;
	}
	
	_logger << Logger::NEUTRAL << "Attempting to crack " << Color::FG_YELLOW << digests.size() << Color::RESET << " digests." << std::endl;
	_logger << Logger::NEUTRAL << "Strategy is to use: " << strategyToString() << "." << std::endl;

	for (auto& attack : _strategy) {
		_logger << Logger::NEUTRAL << "Using attack: " << Color::FG_YELLOW << attack->name() << Color::RESET << std::endl;
		attack->crack(digests, results);

		// All digests have been cracked
		if (results.size() == digests.size()) {
			break;
		}
	}

	_logger << Logger::NEUTRAL << "Found " << results.size() << "/" << digests.size() << " passwords" << std::endl;
	
	if (results.size() > 0) {
		for (auto& result : results) {
			_logger << Logger::SUCCESS << *(result.digest) << " : " << Color::BOLD << *(result.password) << Color::RESET << std::endl;
		}
	} else {
		_logger.error("Unable to crack any digest.");
	}

	_logger.log("Elapsed time: " + std::to_string(
		std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count()
	) + "ms");

	return results.size() > 0;
}

void	Cracker::addAttack(std::shared_ptr<IAttack> attack)
{
	_strategy.push_back(attack);
}
