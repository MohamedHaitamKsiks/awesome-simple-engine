#ifndef __ASENGINE_LUA_RUNTIME_H
#define __ASENGINE_LUA_RUNTIME_H

#include "Core/Singleton/Singleton.h"
#include "ECS/System.h"

#include "LuaState.h"

#include <memory>

namespace ASEngine
{
    // the lua state 
    class LuaRuntime: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(LuaRuntime);
    public:
        ~LuaRuntime();

    protected:
        friend class LuaCppClassBase;

        template <typename T>
        friend class LuaCppClass;

        friend class LuaScript;
        friend class LuaCppClassManager;

        friend class LuaCppClassTest;
        friend class LuaScriptTest;

        inline LuaState &GetState()
        {
            return *m_State;
        }
        
    private:
        std::unique_ptr<LuaState> m_State = nullptr;
        
        void Init() override;
    };  
} // namespace ASEngine


#endif // __ASENGINE_LUA_RUNTIME_H