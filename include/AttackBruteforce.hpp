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
	AttackBruteforce(const std::string &characterSet = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*", const unsigned int maxLength = 8);
	~AttackBruteforce();
	
	IAttack::results	crack(const Hash::md5digest &digest, const size_t length);
	IAttack::results	crack(const Hash::md5digest &digest);
	const std::string&	name();
	void				describe();
};

#endif
