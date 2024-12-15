#ifndef __ASENGINE_LUA_POINTER_H
#define __ASENGINE_LUA_POINTER_H

namespace ASEngine
{
    // lua pointer to cpp object
    // pointer can or not own
    struct LuaPointer
    {
        void* Pointer = nullptr;
        bool Owned = false;
    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_POINTER_H
