#ifndef IATTACK_HPP
#define IATTACK_HPP

#include <string>

class IAttack
{
public:
	virtual std::string&		crack(const std::string &digest) = 0;
	virtual const std::string&	name() = 0;
};

#endif
