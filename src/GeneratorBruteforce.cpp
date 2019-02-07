#include <string>
#include "GeneratorBruteforce.hpp"

GeneratorBruteforce::GeneratorBruteforce(const std::string& characterSet, const size_t minLength, const size_t maxLength)
	: _name("Bruteforce"), _characterSet(characterSet), _setLength(characterSet.length()), _maxLength(maxLength), _done(false)
{
	resetState(minLength);
}
GeneratorBruteforce::~GeneratorBruteforce() {}

/**
 * Sets a new length
 * Initializes all indices to zero
 * Initializes string with first character from set
 */
void						GeneratorBruteforce::resetState(const size_t length)
{
	_state.length = length;
	_state.indices.assign(length, 0);
	_state.password.assign(length, _characterSet.front());
}

GeneratorBruteforce::operator bool() const
{
	return !_done;
}

std::string&				GeneratorBruteforce::operator*()
{
	return _state.password;
}

std::string*				GeneratorBruteforce::operator->()
{
	return &(_state.password);
}

/**
 * Generate next string
 */
GeneratorBruteforce&		GeneratorBruteforce::operator++()
{
	for (int n = _state.length - 1; n >= 0; n--) {
		_state.indices[n]++;

		// Last letter from set
		if (_state.indices[n] >= _setLength) {
			// The letter that wrapped is not the first one, so we go on and reset this one
			if (n > 0) {
				_state.indices[n] = 0;
				_state.password[n] = _characterSet[_state.indices[n]];
			// First letter wrapped, all possibillities have been checked. Increment length and reset password
			} else if (_state.length < _maxLength) {
				resetState(_state.length + 1);
			// First letter wrapped, length is already at max. We stop here
			} else {
				_done = true;
			}
		// Still going in the set. We end the loop here
		} else {
			_state.password[n] = _characterSet[_state.indices[n]];
			break;
		}
	}
	return *this;
}

const std::string&	GeneratorBruteforce::name()
{
	return _name;
}

const std::string	GeneratorBruteforce::describe()
{
	return "Max length is " + std::to_string(_maxLength) + " with the following charset: " + _characterSet;
}
