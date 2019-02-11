#include <iostream>
#include <fstream>
#include "AttackDictionary.hpp"

AttackDictionary::AttackDictionary(const std::string &dictionaryPath)
	: _name("Dictionary"), _logger(Logger(std::cout, "dictionary")), _dictionaryPath(dictionaryPath)
{}
AttackDictionary::~AttackDictionary() {}

IAttack::results		AttackDictionary::crack(const HashMD5& digest)
{
	const std::string	path(_dictionaryPath);
	std::ifstream		dictionary(path);
	IAttack::results	results { false, std::make_unique<HashMD5>(digest), nullptr };

	_logger.log(description());

	if (dictionary.is_open()) {
		std::string password;

		while (std::getline(dictionary, password)) {
			if (digest.check(password)) {
				results.success = true;
				results.password = std::make_unique<std::string>(password);
				break;
			}
		}
		dictionary.close();
	} else {
		_logger.error("Could not open config file (" + path + ")");
	}

	if (results.success) {
		_logger.success("Found");
	} else {
		_logger.warn("Not found");
	}

	return results;
}

const std::string&	AttackDictionary::name()
{
	return _name;
}

const std::string	AttackDictionary::description()
{
	return "Dictionary fetched from file: " + _dictionaryPath;
}
