#include "LuaCppEnum.h"

namespace ASEngine
{
    LuaCppEnum::LuaCppEnum(const std::string &name): LuaCppType(name)
    {
    }

    LuaCppEnum::~LuaCppEnum()
    {
    }

    void LuaCppEnum::BindValue(const std::string &name, LuaInteger value)
    {
        m_Values[name] = value;
    }

} // namespace ASEngine
