#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

class Logger
{
private:
	std::ostream&	_out;

public:
	Logger(std::ostream &out);
	~Logger();

	enum symbol {
		NEUTRAL,
		SUCCESS,
		WARNING,
		ERROR
	};

	void success(const std::string &message);
	void warn(const std::string &message);
	void error(const std::string &message);
};

std::ostream & operator<<(std::ostream & os, const Logger::symbol & symbol);

#endif
