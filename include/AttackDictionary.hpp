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

	bool				check(const std::string &password, const Hash::md5digest &digest);

public:
	AttackDictionary(const std::string &dictionaryPath);
	~AttackDictionary();
	
	IAttack::results	crack(const Hash::md5digest &digest);
	const std::string&	name();
};

#endif
