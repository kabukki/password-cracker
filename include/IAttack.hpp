#ifndef IATTACK_HPP
#define IATTACK_HPP

#include <string>
#include <memory>
#include <chrono>
#include <vector>
#include "Hash.hpp"

class IAttack
{
public:
	struct results {
		bool							success;
		std::unique_ptr<std::string>	password;
		std::chrono::milliseconds		duration;
	};

	virtual IAttack::results	crack(const Hash::md5digest &digest) = 0;
	virtual const std::string&	name() = 0;
	virtual const std::string	description() = 0;
};

#endif
