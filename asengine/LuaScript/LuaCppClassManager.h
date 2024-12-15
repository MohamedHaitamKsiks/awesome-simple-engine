#ifndef __ASENGINE_LUA_CPP_CLASS_MANAGER_H
#define __ASENGINE_LUA_CPP_CLASS_MANAGER_H

#include <unordered_map>

#include "Core/Singleton/Singleton.h"
#include "Core/String/UniqueString.h"

#include "Class/Class.h"
#include "ECS/System.h"
#include "LuaScript/LuaCppClassBuilder.h"

namespace ASEngine
{
    class LuaCppClassManager: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(LuaCppClassManager);
    public:
        ~LuaCppClassManager() {}

        // owner ship is transfered to the manager
        void RegisterLuaCppClass(std::unique_ptr<LuaCppClassBuilder> builder);

        // get metatable name for class
        template<typename T>
        inline UniqueString GetMetatableName() const
        {
            return GetMetatableName(Class<T>::GetName());
        }

        // get metatable name from classname
        inline UniqueString GetMetatableName(UniqueString className) const
        {
            return m_MetatableNames.at(className);
        }

    private:
        std::unordered_map<UniqueString, UniqueString> m_MetatableNames{};
        std::unordered_map<UniqueString, std::unique_ptr<LuaCppClassBuilder>> m_CppClassBuilders = {};

        // build lua class from cpp class
        void Build(const LuaCppClassBuilder& builder);

        void Init() override;
    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_CPP_CLASS_MANAGER_H
