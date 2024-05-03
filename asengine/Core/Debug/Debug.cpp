

#include "Debug.h"

namespace ASEngine {

	std::string Debug::Colorized(Debug::TextColor color, const std::string &str)
	{
		std::stringstream ss;
		ss << "\x1B[" << color << "m" << str << "\033[0m";
		return ss.str();
	}
	
} // ASEngine
