#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

class Logger
{
private:
	std::ostream&		_out;
	const std::string	_name;

public:
	Logger(std::ostream &out, const std::string &name = "-");
	~Logger();

	enum symbol {
		NEUTRAL,
		SUCCESS,
		WARNING,
		ERROR
	};

	void log(const std::string &message) const;
	void success(const std::string &message) const;
	void warn(const std::string &message) const;
	void error(const std::string &message) const;

	std::ostream&		out() const;
	const std::string&	name() const;
};

std::ostream & operator<<(const Logger &logger, const Logger::symbol &symbol);
// std::ostream & operator<<(Logger &logger, const std::string &message);

#endif
