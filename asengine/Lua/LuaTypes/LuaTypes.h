#ifndef __ASENGINE_LUA_TYPES_H
#define __ASENGINE_LUA_TYPES_H

#include <cstdint>

namespace ASEngine
{
    using LuaInteger = int64_t;
    
    using LuaNumber = double;

    using LuaFunction = std::function<int()>;

    using LuaString = std::string;
} // namespace ASEngine


#endif // __ASENGINE_LUA_TYPES_H