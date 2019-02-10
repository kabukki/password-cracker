#ifndef ATTACK_BRUTEFORCE_HPP
#define ATTACK_BRUTEFORCE_HPP

#include <map>
#include "IAttack.hpp"
#include "Logger.hpp"

#define NUM_THREADS	1

class AttackBruteforce : public IAttack
{
private:
	const std::string			_name;
	Logger						_logger;
	const std::string			_charset;
	const size_t				_charsetLength;
	const size_t				_maxLength;
	// Map of <length, possibilities> used to avoid redundant use of std::pow
	std::map<size_t, size_t>	_pow;
	size_t						_possibilities;

	std::string			nthString(const size_t n);

public:
	AttackBruteforce(const std::string &charset = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*", const size_t maxLength = 8);
	~AttackBruteforce();
	
	IAttack::results	crack(const Hash::md5digest &digest) override;
	const std::string&	name() override;
	const std::string	describe() override;
};

#endif
