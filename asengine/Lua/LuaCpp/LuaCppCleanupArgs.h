#ifndef __ASENGINE_LUA_CPP_CLEANUP_ARGS_H
#define __ASENGINE_LUA_CPP_CLEANUP_ARGS_H

namespace ASEngine
{
    // cleanup arg types to be compatible with lua functions
    // pass strings and by value => remove reference if found
    template <typename T>
    struct LuaCppCleanupArg
    {
        using Type = T;
    };

    template <>
    struct LuaCppCleanupArg<const std::string&>
    {
        using Type = std::string;
    };

    template <>
    struct LuaCppCleanupArg<std::string &>
    {
        using Type = std::string;
    };

    template <typename T>
    using LuaCppCleanupArgT = typename LuaCppCleanupArg<T>::Type;
} // namespace ASEngine


#endif 