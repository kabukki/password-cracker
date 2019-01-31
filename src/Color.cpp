#include "Color.hpp"

std::ostream & operator<<(std::ostream & os, const Color::code & code) {
	return os << "\033[" << static_cast<int>(code) << "m";
};
