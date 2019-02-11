#include "Color.hpp"

std::ostream & operator<<(std::ostream& os, const Color::code& code) {
#if ENABLE_COLORS
	return os << "\033[" << static_cast<int>(code) << "m";
#else
	(void)code;
	return os;
#endif
};
