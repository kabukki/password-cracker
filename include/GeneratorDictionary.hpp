#ifndef GENERATOR_DICTIONARY_HPP
#define GENERATOR_DICTIONARY_HPP

#include <fstream>
#include "IGenerator.hpp"

class GeneratorDictionary : public IGenerator
{
private:
	struct state {
		std::string			password;
	};

	const std::string		_name;
	const std::string		_dictionaryPath;
	std::ifstream			_dictionary;
	struct state			_state;

public:
	GeneratorDictionary(const std::string& dictionaryPath);
	~GeneratorDictionary();

	explicit				operator bool() const override;
	reference				operator*() override;
	pointer					operator->() override;
	GeneratorDictionary&	operator++() override;

	const std::string&		name() override;
	const std::string		describe() override;
};

#endif
