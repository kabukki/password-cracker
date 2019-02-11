#include <algorithm>
#include <iostream>
#include <fstream>
#include "AttackDictionary.hpp"
#include "Color.hpp"

AttackDictionary::AttackDictionary(const std::string &dictionaryPath)
	: _name("Dictionary"), _logger(Logger(std::cout, "dictionary")), _dictionaryPath(dictionaryPath)
{}
AttackDictionary::~AttackDictionary() {}

void				AttackDictionary::crack(std::vector<IAttack::pair>& list)
{
	std::ifstream	dictionary(_dictionaryPath);
	size_t			nbCrackedBefore = std::count_if(list.begin(), list.end(), [](IAttack::pair& pair) { return pair.isCracked(); });
	bool			done = false;

	_logger.log(description());

	if (dictionary.is_open()) {
		std::string password;

		while (!done && std::getline(dictionary, password)) {
			for (auto& pair : list) {
				if (pair.digest->check(password)) {
					_logger << Logger::SUCCESS << *(pair.digest) << " : " << Color::BOLD << password << Color::RESET << std::endl;
					pair.password = std::make_unique<std::string>(password);
					// If all digests have been cracked, end here.
					if (std::all_of(list.begin(), list.end(), [](IAttack::pair& pair) { return pair.isCracked(); })) {
						done = true;
						break;
					}
				}
			}
		}
		dictionary.close();
	} else {
		_logger.error("Could not open config file (" + _dictionaryPath + ")");
	}

	if (std::count_if(list.begin(), list.end(), [](IAttack::pair& pair) { return pair.isCracked(); }) - nbCrackedBefore == 0) {
		_logger.warn("Did not find any password");
	}
}

const std::string&	AttackDictionary::name()
{
	return _name;
}

const std::string	AttackDictionary::description()
{
	return "Dictionary fetched from file: " + _dictionaryPath;
}
