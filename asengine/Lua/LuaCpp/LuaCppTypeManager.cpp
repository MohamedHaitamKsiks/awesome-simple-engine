#include "LuaCppTypeManager.h"
#include "Core/String/UniqueStringManager.h"
#include "Lua/LuaRuntime/LuaRuntime.h"

namespace ASEngine
{

    void LuaCppTypeManager::RegisterLuaCppClass(LuaCppClassBase& builder)
    {
        LuaState& state = LuaRuntime::GetInstance().GetState();
        LuaInteger metatableID = state.AddLuaCppClass(builder);
        m_MetatableIDs[builder.GetName()] = metatableID;
    }


    void LuaCppTypeManager::Init()
    {
    }

} // namespace ASEngine
