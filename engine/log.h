//
// Created by ksiks_wa3r on 3/20/23.
//

#ifndef MY_APPLICATION_LOG_H
#define MY_APPLICATION_LOG_H

#include <android/log.h>

#define  LOG_TAG "ASEngine"
#define  ALOG(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)

#endif //MY_APPLICATION_LOG_H
