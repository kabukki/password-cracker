#ifndef IATTACK_HPP
#define IATTACK_HPP

#include <string>
#include <memory>
#include "Hash.hpp"

class IAttack
{
public:
	struct results {
		bool							success;
		std::unique_ptr<std::string>	password;
		unsigned int					attempts;
	};

	virtual IAttack::results	crack(const Hash::md5digest &digest) = 0;
	virtual const std::string&	name() = 0;
	virtual const std::string	describe() = 0;
};

#endif
