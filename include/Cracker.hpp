#ifndef CRACKER_HPP
#define CRACKER_HPP

#include <memory>
#include <vector>
#include "IAttack.hpp"
#include "Logger.hpp"
#include "HashMD5.hpp"

class Cracker
{
private:
	std::vector<std::shared_ptr<IAttack>>		_strategy;
	Logger										_logger;

	std::string	strategyToString() const;

public:
	struct results {
		bool							success;
		std::unique_ptr<std::string>	password;
		unsigned int					attempts;
	};

	Cracker();
	~Cracker();

	bool		crack(const std::vector<HashMD5> digests);
	void		addAttack(std::shared_ptr<IAttack> attack);
};

#endif
