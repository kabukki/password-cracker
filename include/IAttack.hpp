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

	virtual void				crack(const std::vector<DigestMD5> digests, std::vector<IAttack::results>& results) = 0;
	virtual const std::string&	name() = 0;
	virtual const std::string	description() = 0;
};

#endif
