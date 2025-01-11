#ifndef __ASENGINE_LUA_CPP_TYPE_MANAGER_H
#define __ASENGINE_LUA_CPP_TYPE_MANAGER_H

#include <unordered_map>

#include "Core/Singleton/Singleton.h"
#include "Core/String/UniqueString.h"

#include "Class/Class.h"
#include "ECS/System.h"

#include "LuaCppType.h"
#include "LuaCppClassBase.h"

namespace ASEngine
{
    class LuaCppTypeManager: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(LuaCppTypeManager);
    public:
        ~LuaCppTypeManager() {}

        // owner ship is transfered to the manager
        void RegisterLuaCppClass(LuaCppClassBase& builder);

        // get metatable name from classname
        inline int GetMetatableID(UniqueString className) const
        {
            return m_MetatableIDs.at(className);
        }

    private:
        friend class LuaCppClassBase;
        std::unordered_map<UniqueString, LuaInteger> m_MetatableIDs {};

        void Init() override;
    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_CPP_TYPE_MANAGER_H
