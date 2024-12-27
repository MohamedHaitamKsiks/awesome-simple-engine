#ifndef __ASENGINE_LUA_CPP_CLASS_BUILDER_H
#define __ASENGINE_LUA_CPP_CLASS_BUILDER_H

#include "Core/String/UniqueString.h"

#include "LuaCppFunction.h"
#include "Lua/LuaTypes/LuaUserdata.h"

#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace ASEngine
{
    // to build a c++ class binding to lua
    // just a data structure with no logic
    class LuaCppClassBase
    {
    public:
        struct MethodBinding
        {
            LuaCppFunction Method;
            bool IsStatic = false;
        };

        LuaCppClassBase(UniqueString className, UniqueString parentClassName);
        virtual ~LuaCppClassBase() {};

        void BindBaseMethod(UniqueString name, std::function<int()> method, bool isStatic);

    private:
        friend class LuaCppClassManager;

        UniqueString m_ClassName;
        UniqueString m_MetatableName; // unique and generated from the class name
        UniqueString m_ParentClassName;

        std::unordered_map<UniqueString, MethodBinding> m_MethodBindings{};
    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_CPP_CLASS_BUILDER_H
