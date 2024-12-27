#include "LuaRuntime.h"

#include "Backend/LuaStateImp.h"

namespace ASEngine
{
    LuaRuntime::~LuaRuntime()
    {
    }

    void LuaRuntime::Init()
    {
        m_State = std::make_unique<LuaStateImp>();
        m_State->Run(R"lua(
            print('Lua is active!')
        )lua");
    }

} // namespace ASEngine
