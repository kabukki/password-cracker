#include "GeneratorDictionary.hpp"

GeneratorDictionary::GeneratorDictionary(const std::string& dictionaryPath)
	: _name("Dictionary"), _dictionaryPath(dictionaryPath)
{
	_dictionary = std::ifstream(dictionaryPath);
	++*this;
}
GeneratorDictionary::~GeneratorDictionary()
{
	if (_dictionary.is_open()) {
		_dictionary.close();
	}
}

GeneratorDictionary::operator bool() const
{
	return !_dictionary.fail();
}

std::string&				GeneratorDictionary::operator*()
{
	return _state.password;
}

std::string*				GeneratorDictionary::operator->()
{
	return &(_state.password);
}

GeneratorDictionary&	GeneratorDictionary::operator++()
{
	if (*this) {
		std::getline(_dictionary, _state.password);
	}
}

const std::string&	GeneratorDictionary::name()
{
	return _name;
}

const std::string	GeneratorDictionary::describe()
{
	return "Dictionary fetched from file: " + _dictionaryPath;
}
