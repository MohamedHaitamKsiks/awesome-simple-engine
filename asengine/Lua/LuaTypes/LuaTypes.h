#ifndef __ASENGINE_LUA_TYPES_H
#define __ASENGINE_LUA_TYPES_H

#include <cstdint>
#include <string>
#include <functional>

namespace ASEngine
{
    using LuaBoolean = bool;

    using LuaInteger = int64_t;
    
    using LuaNumber = double;

    class LuaState;
    using LuaCppFunction = std::function<int(LuaState&)>;

    using LuaString = std::string;
} // namespace ASEngine


#endif // __ASENGINE_LUA_TYPES_H