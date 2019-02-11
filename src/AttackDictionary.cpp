#include <iostream>
#include <fstream>
#include "AttackDictionary.hpp"
#include "Color.hpp"

AttackDictionary::AttackDictionary(const std::string &dictionaryPath)
	: _name("Dictionary"), _logger(Logger(std::cout, "dictionary")), _dictionaryPath(dictionaryPath)
{}
AttackDictionary::~AttackDictionary() {}

void				AttackDictionary::crack(const std::vector<HashMD5> digests, std::vector<IAttack::results>& results)
{
	std::ifstream	dictionary(_dictionaryPath);
	size_t			resultsSizeBefore = results.size();
	bool			done = false;

	_logger.log(description());

	if (dictionary.is_open()) {
		std::string password;

		while (!done && std::getline(dictionary, password)) {
			for (auto& digest : digests) {
				if (digest.check(password)) {
					_logger << Logger::SUCCESS << digest << " : " << Color::BOLD << password << Color::RESET << std::endl;
					results.push_back(IAttack::results {
						std::make_unique<HashMD5>(digest),
						std::make_unique<std::string>(password)
					});
				}
				if (results.size() == digests.size()) {
					done = false;
					break;
				}
			}
		}
		dictionary.close();
	} else {
		_logger.error("Could not open config file (" + _dictionaryPath + ")");
	}

	if (results.size() - resultsSizeBefore == 0) {
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
