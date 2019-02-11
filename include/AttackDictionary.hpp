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
	
	void				crack(const std::vector<DigestMD5> digests, std::vector<IAttack::results>& results) override;
	const std::string&	name() override;
	const std::string	description() override;
};

#endif
