#ifndef __ASENGINE_LUA_POINTER_H
#define __ASENGINE_LUA_POINTER_H

namespace ASEngine
{
    // lua userdata
    // pointer can or not own
    struct LuaUserdata
    {
        void* Pointer = nullptr;
        bool Owned = false;
    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_POINTER_H
