

#include "Log.h"


#ifdef __ANDROID__

#include <android/log.h>

#define  LOG_TAG "ASEngine"
#define  ALOG(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

namespace ASEngine {

	void Debug::Log(const std::string &message)
	{
		ALOG("%s", message.c_str());
	}

} // ASEngine

#else

#include <iostream>

namespace ASEngine {

	void Debug::Log(const std::string &message) 
	{
		std::cout<< message << "\n";
	}

	std::string Debug::Colorized(Debug::TextColor color, const std::string &str)
	{
		std::stringstream ss;
		ss << "\x1B[" << color << "m" << str << "\033[0m";
		return ss.str();
	}

} // ASEngine

#endif