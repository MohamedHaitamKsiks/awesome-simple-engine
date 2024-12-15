#include "LuaScriptModule.h"
#include "ECS/SystemManager.h"
#include "LuaScript/LuaCppClassBuilder.h"
#include "LuaScript/LuaCppClassManager.h"
#include "LuaScript/LuaScript.h"
#include "LuaScript/LuaScriptManager.h"
#include "Resource/ResourceManager.h"


namespace ASEngine
{
    void LuaScriptModule::Init()
    {
        ASENGINE_REGISTER_SYSTEM(LuaScriptManager);
        ASENGINE_REGISTER_SYSTEM(LuaCppClassManager);
        // ASENGINE_REGISTER_RESOURCE_CLASS(LuaScript);
    }
} // namespace ASEngine
