#include "LuaModule.h"

#include "Lua/LuaScript/LuaScriptManager.h"
#include "Lua/LuaRuntime/LuaRuntime.h"
#include "Lua/LuaCpp/LuaCppClassManager.h"

#include "ECS/SystemManager.h"
#include "Resource/ResourceManager.h"

namespace ASEngine
{
    void LuaModule::Init()
    {
        ASENGINE_REGISTER_SYSTEM(LuaRuntime);
        ASENGINE_REGISTER_SYSTEM(LuaCppClassManager);
        ASENGINE_REGISTER_SYSTEM(LuaScriptManager);
        // ASENGINE_REGISTER_RESOURCE_CLASS(LuaScript);
    }
} // namespace ASEngine
