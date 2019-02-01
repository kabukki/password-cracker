#include "Logger.hpp"
#include "Color.hpp"

Logger::Logger(std::ostream &out)
	: _out(out)
{}
Logger::~Logger() {}

void Logger::success(const std::string &message)
{
	_out << Logger::SUCCESS << message << std::endl;
}

void Logger::warn(const std::string &message)
{
	_out << Logger::WARNING << message << std::endl;
}

void Logger::error(const std::string &message)
{
	_out << Logger::ERROR << message << std::endl;
}

std::ostream & operator<<(std::ostream & os, const Logger::symbol & symbol)
{
	switch (symbol) {
		case Logger::NEUTRAL:
			return os << Color::BOLD << Color::FG_WHITE << "[-] " << Color::RESET;
		case Logger::SUCCESS:
			return os << Color::BOLD << Color::FG_GREEN << "[+] " << Color::RESET;
		case Logger::WARNING:
			return os << Color::BOLD << Color::FG_YELLOW << "[!] " << Color::RESET;
		case Logger::ERROR:
			return os << Color::BOLD << Color::FG_RED << "[-] " << Color::RESET;
		default:
			return os;
	}
}
