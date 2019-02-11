#ifndef ATTACK_BRUTEFORCE_HPP
#define ATTACK_BRUTEFORCE_HPP

#include <map>
#include "IAttack.hpp"
#include "Logger.hpp"

#define NUM_THREADS	4

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

	std::string					nthString(const size_t n);

public:
	AttackBruteforce(const std::string &charset = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*", const size_t maxLength = 8);
	~AttackBruteforce();
	
	void				crack(const std::vector<HashMD5> digests, std::vector<IAttack::results>& results) override;
	const std::string&	name() override;
	const std::string	description() override;
};

#endif
