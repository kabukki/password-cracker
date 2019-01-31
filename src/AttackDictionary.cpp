#include <iostream>
#include <fstream>
#include "AttackDictionary.hpp"

AttackDictionary::AttackDictionary()
	: _name("Dictionary"), _logger(Logger(std::cout))
{}
AttackDictionary::~AttackDictionary() {}

std::string&	AttackDictionary::crack(const std::string &digest)
{
	const std::string path("mots-8-et-moins.txt");
	std::ifstream dictionary(path);

	if (dictionary.is_open()) {
		std::string line;
		size_t n = 0;
		while (std::getline(dictionary, line)) {
			n++;
		}
		std::cout << "Read " << n << " entries" << std::endl;
		dictionary.close();
	} else {
		_logger.error("Could not open config file (" + path + ")");
	}
}

const std::string&	AttackDictionary::name()
{
	return _name;
}
