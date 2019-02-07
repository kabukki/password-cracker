#ifndef CRACKER_HPP
#define CRACKER_HPP

#include <memory>
#include <vector>
#include "IGenerator.hpp"
#include "Logger.hpp"
#include "Hash.hpp"

class Cracker
{
private:
	std::vector<std::shared_ptr<IGenerator>>	_strategy;
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

	bool		crack(const Hash::md5digest &digest);
	void		addGenerator(std::shared_ptr<IGenerator> generator);
};

#endif
