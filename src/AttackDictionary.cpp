#include <iostream>
#include <fstream>
#include "AttackDictionary.hpp"
#include "Hash.hpp"

AttackDictionary::AttackDictionary(const std::string &dictionaryPath)
	: _name("Dictionary"), _logger(Logger(std::cout)), _dictionaryPath(dictionaryPath)
{}
AttackDictionary::~AttackDictionary() {}

IAttack::results	AttackDictionary::crack(const Hash::md5digest &digest)
{
	const std::string path(_dictionaryPath);
	std::ifstream dictionary(path);
	IAttack::results results { false, nullptr, 0 };

	if (dictionary.is_open()) {
		std::string password;

		while (std::getline(dictionary, password)) {
			results.attempts++;
			if (Hash::check(password, digest)) {
				results.success = true;
				results.password = std::make_unique<std::string>(password);
				break;
			}
		}
		dictionary.close();
	} else {
		_logger.error("Could not open config file (" + path + ")");
	}
	return results;
}

const std::string&	AttackDictionary::name()
{
	return _name;
}
