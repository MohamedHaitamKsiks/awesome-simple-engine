#include "Debug.h"
#include <android/log.h>

#define LOG_TAG "ASEngine"
#define ALOG(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

namespace ASEngine
{
    void Debug::Log(const std::string &message)
    {
        ALOG("%s", message.c_str());
    }
} // ASEngine