#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

namespace Color
{
	enum code {
		/* Foreground */
		FG_BLACK    = 30,
		FG_RED      = 31,
		FG_GREEN    = 32,
		FG_YELLOW   = 33,
		FG_BLUE     = 34,
		FG_MAGENTA  = 35,
		FG_CYAN     = 36,
		FG_WHITE    = 37,
		FG_DEFAULT  = 39,
		/* Background */
		BG_BLACK    = 40,
		BG_RED      = 41,
		BG_GREEN    = 42,
		BG_YELLOW   = 43,
		BG_BLUE     = 44,
		BG_MAGENTA  = 45,
		BG_CYAN     = 46,
		BG_WHITE    = 47,
		BG_DEFAULT  = 49,
		/* Styles */
		RESET       = 0,
		BOLD        = 1,
		DIM         = 2,
		UNDERLINE   = 4,
		BLINK       = 5,
		INVERTED    = 7,
		HIDDEN      = 8
	};

};

std::ostream & operator<<(std::ostream & os, const Color::code & code);

#endif
