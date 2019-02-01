#ifndef ATTACK_BRUTEFORCE_HPP
#define ATTACK_BRUTEFORCE_HPP

#include "IAttack.hpp"
#include "Logger.hpp"

class AttackBruteforce : public IAttack
{
private:
	const std::string	_name;
	Logger				_logger;
	const std::string	_characterSet;
	const unsigned int	_maxLength;

public:
	AttackBruteforce();
	~AttackBruteforce();
	
	IAttack::results	crack(const Hash::md5digest &digest);
	const std::string&	name();
};

#endif