#ifndef IATTACK_HPP
#define IATTACK_HPP

#include <string>
#include <memory>
#include <vector>
#include "DigestMD5.hpp"

class IAttack
{
public:
	struct results {
		std::unique_ptr<DigestMD5>		digest;
		std::unique_ptr<std::string>	password;
	};

	struct pair {
		std::unique_ptr<DigestMD5>		digest;
		std::unique_ptr<std::string>	password;

		bool							isCracked() const { return password != nullptr; }
	};

	virtual void				crack(std::vector<IAttack::pair>& list) = 0;
	virtual const std::string&	name() = 0;
	virtual const std::string	description() = 0;
};

#endif
