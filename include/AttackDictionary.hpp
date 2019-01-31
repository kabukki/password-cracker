#ifndef ATTACK_DICTIONARY_HPP
#define ATTACK_DICTIONARY_HPP

#include "IAttack.hpp"
#include "Logger.hpp"

class AttackDictionary : public IAttack
{
private:
	const std::string	_name;
	Logger				_logger;

public:
	AttackDictionary();
	~AttackDictionary();
	
	std::string&		crack(const std::string &digest);
	const std::string&	name();
};

#endif
