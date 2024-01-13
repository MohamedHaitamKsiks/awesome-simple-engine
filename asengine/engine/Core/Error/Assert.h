#ifndef ASENGINE_ASSERT_H
#define ASENGINE_ASSERT_H

#include "Core/Log/Log.h"
#include <cassert>

#define ASSERT(predicat, message) assert(((void)(Debug::Colorized(Debug::TextColor::RED_FG, message).c_str()), predicat))

#endif // ASENGINE_ASSERT_H