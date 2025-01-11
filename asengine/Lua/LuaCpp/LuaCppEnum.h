#ifndef ASENGINE_LUA_CPP_ENUM_H
#define ASENGINE_LUA_CPP_ENUM_H

#include "Macros/Foreach.h"

#include "Lua/LuaTypes/LuaTypes.h"
#include "LuaCppType.h"

#include <unordered_map>


// begin binding area, you can NOT begin a binding area inside another binding area
#define __ASENGINE_LUA_CPP_ENUM_BEGIN(enumToBind) { \
    using __luaEnumToBind = enumToBind; \
    ASEngine::LuaCppEnum<enumToBind> __luaCppEnum(#enumToBind);

// end binding area
#define __ASENGINE_LUA_CPP_ENUM_END() \
    ASEngine::LuaCppTypeManager::GetInstance().RegisterLuaCppEnum(__luaCppEnum); }


// bind value
#define __ASENGINE_BIND_ENUM_VALUE(value) \
    __luaCppEnum.BindValue(#value, static_cast<LuaInteger>(__luaEnumToBind::value));

// lua cpp 
#define ASENGINE_LUA_CPP_ENUM(enumToBind, ...) { \
     using __luaEnumToBind = enumToBind; \
    ASEngine::LuaCppEnum __luaCppEnum(#enumToBind); \
    FOREACH(__ASENGINE_BIND_ENUM_VALUE, __VA_ARGS__); \
    ASEngine::LuaCppTypeManager::GetInstance().RegisterLuaCppEnum(__luaCppEnum); }


namespace ASEngine
{
    class LuaCppEnum: public LuaCppType
    {
    public:
        LuaCppEnum(const std::string& name);
        ~LuaCppEnum();

        void BindValue(const std::string& name, LuaInteger value);

        inline const std::unordered_map<std::string, LuaInteger>& GetValues() const
        {
            return m_Values;
        }
    private:
        friend class LuaCppTypeManager;
        std::unordered_map<std::string, LuaInteger> m_Values;

    };
} // namespace ASEngine


#endif // ASENGINE_LUA_CPP_ENUM_H