#ifndef ASENGINE_LUA_CPP_ENUM_H
#define ASENGINE_LUA_CPP_ENUM_H

#include "Lua/LuaTypes/LuaTypes.h"
#include "LuaCppType.h"


#include <unordered_map>

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