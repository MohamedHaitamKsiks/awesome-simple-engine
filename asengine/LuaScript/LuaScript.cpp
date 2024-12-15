#include "LuaScript.h"
#include "Core/FileSystem/File.h"
#include "LuaScriptManager.h"

namespace ASEngine
{
    void LuaScript::Create(const std::string& luaSource)
    {
        auto& luaState = LuaScriptManager::GetInstance().GetState();
        luaState.Run(luaSource);
    }

    bool LuaScript::Load(const std::string& path)
    {
        File scriptFile{};
        if (!scriptFile.Open(path))
        {
            return false;
        }

        Create(scriptFile.ReadText());
        SetPersistent(true); // lua script are saved once loaded

        return true;
    }
} // namespace ASEngine
