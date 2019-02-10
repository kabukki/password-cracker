#ifndef ATTACK_DICTIONARY_HPP
#define ATTACK_DICTIONARY_HPP

#include "IAttack.hpp"
#include "Logger.hpp"

class AttackDictionary : public IAttack
{
private:
	const std::string	_name;
	Logger				_logger;
	const std::string	_dictionaryPath;

public:
	AttackDictionary(const std::string &dictionaryPath);
	~AttackDictionary();
	
	IAttack::results	crack(const Hash::md5digest &digest) override;
	const std::string&	name() override;
	const std::string	describe() override;
};

#endif
