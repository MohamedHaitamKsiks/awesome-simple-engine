#ifndef __ASENGINE_LUA_SCRIPT_SYSTEM_H
#define __ASENGINE_LUA_SCRIPT_SYSTEM_H

#include "Core/Signal/Signal.h"
#include "Core/String/UniqueString.h"
#include "Core/Singleton/Singleton.h"

#include "ECS/Entity.h"
#include "ECS/System.h"

#include "LuaScript/LuaCppClassBuilder.h"
#include "LuaScript/LuaState.h"
#include <unordered_map>

namespace ASEngine
{
    class LuaScriptManager: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(LuaScriptManager);
    public:
        ~LuaScriptManager() {}

    private:
        std::unique_ptr<LuaState> m_State = nullptr;

        void Init() override;
        void Update(float delta) override {};
        void FixedUpdate(float delta) override {};
        void OnInputEvent(const InputEvent &event) override {};
        void Terminate() override {};

        void ScriptInstanceCreate(UniqueString className, EntityID entityID);

        friend class LuaCppClassBuilder;
        template<typename T> friend class LuaCppClass;

        friend class LuaScript;
        friend class LuaCppClassManager;

        friend class LuaCppClassTest;
        friend class LuaScriptTest;

        inline LuaState& GetState()
        {
            return *m_State;
        }
    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_SCRIPT_SYSTEM_H
