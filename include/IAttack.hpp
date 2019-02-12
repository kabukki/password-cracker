#ifndef IATTACK_HPP
#define IATTACK_HPP

#include <string>
#include <memory>
#include <vector>
#include "ADigest.hpp"

class IAttack
{
public:
	struct pair {
		std::unique_ptr<ADigest>		digest;
		std::unique_ptr<std::string>	password;

		bool							isCracked() const { return password != nullptr; }
	};

	virtual void						crack(std::vector<IAttack::pair>& list) const = 0;
	virtual const std::string&			name() const = 0;
	virtual const std::string			description() const = 0;
};

#endif
