#ifndef __ASENGINE_LUA_CPP_CLASS_BUILDER_H
#define __ASENGINE_LUA_CPP_CLASS_BUILDER_H

#include "Core/String/UniqueString.h"

#include "Lua/LuaTypes/LuaTypes.h"
#include "LuaCppType.h"

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
    class LuaCppClassBase: public LuaCppType
    {
    public:
        struct MethodBinding
        {
            LuaCppFunction Method;
            bool IsStatic = false;
        };

        LuaCppClassBase(UniqueString className, UniqueString parentClassName);
        virtual ~LuaCppClassBase() {};

        void BindCppFunction(const std::string& name, LuaCppFunction method, bool isStatic);

        inline UniqueString GetParentName() const
        {
            return m_ParentClassName;
        }

        template<typename T>
        void SetSingleton(T& singleton)
        {
            m_Singleton = reinterpret_cast<void*>(&singleton);
        }

        inline void* GetSingleton() const
        {
            return m_Singleton;
        }

        std::unordered_map<std::string, LuaCppFunction> GetMethods() const;
        std::unordered_map<std::string, LuaCppFunction> GetStaticMethods() const;

    private:
        UniqueString m_ParentClassName;
        void* m_Singleton = nullptr;
        std::unordered_map<std::string, MethodBinding> m_MethodBindings{};
    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_CPP_CLASS_BUILDER_H
