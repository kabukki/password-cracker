#ifndef CRACKER_HPP
#define CRACKER_HPP

#include <memory>
#include <vector>
#include "IAttack.hpp"
#include "Logger.hpp"

class Cracker
{
private:
	std::vector<std::shared_ptr<IAttack>>		_strategy;
	Logger										_logger;

	std::string	strategyToString() const;

public:
	Cracker();
	~Cracker();

	bool		crack(std::vector<IAttack::pair>& list);
	void		addAttack(std::shared_ptr<IAttack> attack);
};

#endif
