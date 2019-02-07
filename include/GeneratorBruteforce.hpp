#ifndef GENERATOR_BRUTEFORCE_HPP
#define GENERATOR_BRUTEFORCE_HPP

#include <vector>
#include "IGenerator.hpp"

class GeneratorBruteforce : public IGenerator
{
private:
	struct state {
		size_t					length;
		std::vector<size_t>		indices;
		std::string				password;
	};

	const std::string		_name;
	const std::string		_characterSet;
	const size_t			_setLength;
	const size_t			_maxLength;
	struct state			_state;
	bool					_done;

	void					resetState(const size_t length);

public:
	GeneratorBruteforce(const std::string& characterSet = "abcdefghijklmnopqrstuvwxyz0123456789!@#$%&*", const size_t minLength = 1, const size_t maxLength = 8);
	~GeneratorBruteforce();

	explicit				operator bool() const override;
	reference				operator*() override;
	pointer					operator->() override;
	GeneratorBruteforce&	operator++() override;

	const std::string&		name() override;
	const std::string		describe() override;
};

#endif
