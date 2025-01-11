#ifndef __ASENGINE_LUA_STATE_IMP_H
#define __ASENGINE_LUA_STATE_IMP_H

#include "Lua/LuaRuntime/LuaRuntime.h"
#include "Lua/LuaRuntime/LuaState.h"

#ifdef __cplusplus
extern "C" {
#endif
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
#ifdef __cplusplus
}
#endif


namespace ASEngine
{
    class LuaStateImp: public LuaState
    {
    public:
        LuaStateImp();
        ~LuaStateImp();


    private:
        lua_State* m_L = nullptr;

        // push function to the stack
        void PushFunction(LuaCppFunction func);

        // add function 
        void AddFunction(const std::string& name, LuaCppFunction function);

        // run code
        void Run(const std::string& script) override;

        // call function by name
        void CallFunction(int position, int argumentsCount, bool doesReturn) override;

        // push integer to the stack
        void PushInteger(int64_t integer) override;

        // push number to the stack
        void PushNumber(double number) override;

        // push string
        void PushString(const std::string &str) override;

        // push boolean
        void PushBoolean(bool value) override;

        // push a pointer to userdata
        void PushUserdata(const LuaUserdata& pointer) override;

        // get integer from stack at index
        int64_t GetInteger(int position) override;

        // get number from stack at index
        double GetNumber(int position) override;

        // get string
        std::string GetString(int position) override;

        // get boolean
        bool GetBoolean(int position) override;

        // get userdata
        void GetUserdata(int position, LuaUserdata& pointer) override;

        // get error
        inline std::string GetError(int result)
        {
            return (result != LUA_OK)? lua_tostring(m_L, -1) : "";
        }

        static int CallCppFunction(lua_State* L);
        static int DestroyCppFunction(lua_State* L);

        LuaInteger AddLuaCppClass(const LuaCppClassBase &luaCppClass) override;

        void AddLuaCppEnum(const LuaCppEnum &luaCppEnum) override;
    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_STATE_IMP_H
