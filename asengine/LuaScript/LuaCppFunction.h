#ifndef __ASENGINE_LUA_CPP_FUNCTION_H
#define __ASENGINE_LUA_CPP_FUNCTION_H

#include "Core/String/UniqueString.h"
namespace ASEngine
{
    struct LuaCppFunction
    {
        using FunctionType = typename std::function<int()>;

        UniqueString Name;
        std::shared_ptr<FunctionType> Function; // returns the number of parameters
    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_CPP_FUNCTION_H
