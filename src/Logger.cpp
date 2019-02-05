#include <iomanip>
#include "Logger.hpp"
#include "Color.hpp"

Logger::Logger(std::ostream &out, const std::string &name)
	: _out(out), _name(name)
{}
Logger::~Logger() {}

void Logger::log(const std::string &message)
{
	*this << Logger::NEUTRAL << message << std::endl;
}

void Logger::success(const std::string &message)
{
	*this << Logger::SUCCESS << message << std::endl;
}

void Logger::warn(const std::string &message)
{
	*this << Logger::WARNING << message << std::endl;
}

void Logger::error(const std::string &message)
{
	*this << Logger::ERROR << message << std::endl;
}

std::ostream&		Logger::out() const
{
	return _out;
}

const std::string&	Logger::name() const
{
	return _name;
}

std::ostream & operator<<(Logger &logger, const Logger::symbol &symbol)
{
	switch (symbol) {
		case Logger::NEUTRAL:
			logger.out() << Color::BOLD << Color::FG_WHITE; break;
		case Logger::SUCCESS:
			logger.out() << Color::BOLD << Color::FG_GREEN; break;
		case Logger::WARNING:
			logger.out() << Color::BOLD << Color::FG_YELLOW; break;
		case Logger::ERROR:
			logger.out() << Color::BOLD << Color::FG_RED; break;
		default:
			return logger.out();
	}
	logger.out() << "[" << std::setfill(' ') << std::setw(10) << logger.name() << "] " << Color::RESET;
	return logger.out();
}

// std::ostream & operator<<(Logger &logger, const std::string &message)
// {
// 	std::cout << "using operator << for logger with message" << std::endl;
// 	return logger.out() << message;
// }
