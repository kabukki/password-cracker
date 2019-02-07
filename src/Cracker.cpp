#include <iostream>
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

bool	Cracker::crack(const Hash::md5digest &digest)
{
	if (_strategy.empty()) {
		_logger.warn("No strategy specified to crack password. Aborting");
		return false;
	}
	
	_logger << Logger::NEUTRAL << "Attempting to crack digest: " << Color::FG_YELLOW << digest << Color::RESET << std::endl;
	_logger << Logger::NEUTRAL << "Strategy is to use: " << strategyToString() << "." << std::endl;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end;

	for (auto& generator : _strategy) {
		Cracker::results results { false, nullptr, 0 };;

		_logger << Logger::NEUTRAL << "Using generator: " << Color::FG_YELLOW << generator->name() << Color::RESET << std::endl;
		_logger << Logger::NEUTRAL << generator->describe() << std::endl;

		while (*generator) {
			// std::cout << **generator << std::endl;
			results.attempts++;
			if (Hash::check(**generator, digest)) {
				results.success = true;
				results.password = std::make_unique<std::string>(**generator);
				break;
			}
			++*(generator);
		}

		if (results.success == true) {
			end = std::chrono::steady_clock::now();
			auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

			_logger << Logger::SUCCESS
				<< "Found password " << Color::BOLD << *(results.password) << Color::RESET
				<< " in " << time << "ms"
				<< " after " << results.attempts << " attempts" << std::endl;
			return true;
		} else {
			_logger.warn("Could not find password using " + generator->name() + " attack.");
		}
	}
	_logger.error("Unable to crack digest.");
	return false;
}

void	Cracker::addGenerator(std::shared_ptr<IGenerator> generator)
{
	_strategy.push_back(generator);
}
