//
// Created by ksiks_wa3r on 5/30/23.
//

#include "Log.h"
#include <android/log.h>

#define  LOG_TAG "ASEngine"
#define  ALOG(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

namespace ASEngine {

	void Log::out(const std::string& message) {
		ALOG("%s", message.c_str());
	}

} // ASEngine