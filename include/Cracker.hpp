#ifndef CRACKER_HPP
#define CRACKER_HPP

#include "IAttack.hpp"

class Cracker
{
private:
	IAttack*	_attack;

public:
	Cracker();
	~Cracker();

	std::string&	crack(const std::string &digest);

};

#endif
