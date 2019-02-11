#include <iostream>
#include <memory>
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

bool					Cracker::crack(const HashMD5& digest)
{
	auto				begin = std::chrono::steady_clock::now();
	IAttack::results	results { false, nullptr, nullptr };

	if (_strategy.empty()) {
		_logger.warn("No strategy specified to crack password. Aborting");
		return false;
	}
	
	_logger << Logger::NEUTRAL << "Attempting to crack digest: " << Color::FG_YELLOW << digest << Color::RESET << std::endl;
	_logger << Logger::NEUTRAL << "Strategy is to use: " << strategyToString() << "." << std::endl;

	for (auto& attack : _strategy) {
		_logger << Logger::NEUTRAL << "Using attack: " << Color::FG_YELLOW << attack->name() << Color::RESET << std::endl;
		results = attack->crack(digest);

		if (results.success == true) {
			break;
		}
	}

	if (results.success) {
		_logger << Logger::SUCCESS << *(results.digest) << " : " << Color::BOLD << *(results.password) << Color::RESET << std::endl;
	} else {
		_logger.error("Unable to crack digest.");
	}

	_logger.log("Elapsed time: " + std::to_string(
		std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - begin).count()
	) + "ms");

	return results.success;
}

void	Cracker::addAttack(std::shared_ptr<IAttack> attack)
{
	_strategy.push_back(attack);
}
