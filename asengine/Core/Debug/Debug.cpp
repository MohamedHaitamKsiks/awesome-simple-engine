

#include "Debug.h"
#include <iostream>

namespace ASEngine 
{

	std::string Debug::Colorized(Debug::TextColor color, const std::string &str)
	{
		std::stringstream ss;
		ss << "\x1B[" << color << "m" << str << "\033[0m";
		return ss.str();
	}

	void Debug::Log(const std::string &message)
	{
		std::cout << message << "\n";
	}

} // ASEngine
