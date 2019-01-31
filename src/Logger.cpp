#include "Logger.hpp"
#include "Color.hpp"

Logger::Logger(std::ostream &out)
	: _out(out)
{}
Logger::~Logger() {}

void Logger::success(const std::string &message)
{
	_out << Color::FG_GREEN << "[+] " << Color::RESET << message << std::endl;
}

void Logger::warn(const std::string &message)
{
	_out << Color::FG_YELLOW << "[!] " << Color::RESET << message << std::endl;
}

void Logger::error(const std::string &message)
{
	_out << Color::FG_RED << "[-] " << Color::RESET << message << std::endl;
}
