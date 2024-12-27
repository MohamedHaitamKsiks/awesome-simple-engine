#include "LuaStateImp.h"

#include "Core/Error/Assertion.h"

#include "Lua/LuaCpp/LuaCppFunction.h"
#include "Lua/LuaTypes/LuaUserdata.h"

#include "lauxlib.h"
#include "lua.h"


#define __ASENGINE_LUA_ASSERT(result) ASENGINE_ASSERT(result == LUA_OK, GetError(result))

namespace ASEngine
{
    LuaStateImp:: LuaStateImp()
    {
        m_L = luaL_newstate();
        luaL_openlibs(m_L);
    }

    LuaStateImp::~LuaStateImp()
    {
        // collect remaining garbage
        int result = lua_gc(m_L, LUA_GCCOLLECT);
        __ASENGINE_LUA_ASSERT(result);

        // close state
        lua_close(m_L);
    }

    void LuaStateImp::Run(const std::string& script)
    {
        int result = luaL_dostring(m_L, script.c_str());
        __ASENGINE_LUA_ASSERT(result);
    }

    int LuaStateImp::CallCppFunction(lua_State* L)
    {
        ASENGINE_ASSERT(lua_islightuserdata(L, 1), "Type Error");

        std::function<int()>& fun = *reinterpret_cast<std::function<int()>*>(
            lua_touserdata(L, 1)
        );
        lua_remove(L, 1);

        return fun();
    }

    // call function by name
    void LuaStateImp::CallFunction(const std::string& functionName, int argumentsCount, bool doesReturn)
    {
        lua_getglobal(m_L, functionName.c_str());
        ASENGINE_ASSERT(lua_isfunction(m_L, -1), "Type Error");

        lua_insert(m_L, - (argumentsCount + 1));

        int result = lua_pcall(m_L, argumentsCount, doesReturn ? 1: 0, 0);
        __ASENGINE_LUA_ASSERT(result);
    }

    // push integer to the stack
    void LuaStateImp::PushInteger(int64_t integer)
    {
        lua_pushinteger(m_L, integer);
    }

    // push number to the stack
    void LuaStateImp::PushNumber(double number)
    {
        lua_pushnumber(m_L, number);
    }

    // push string
    void LuaStateImp::PushString(const std::string &str)
    {
        lua_pushstring(m_L, str.c_str());
    }

    // push boolean
    void LuaStateImp::PushBoolean(bool value)
    {
        lua_pushboolean(m_L, value);
    }

    // push a pointer to userdata
    void LuaStateImp::PushUserdata(const LuaUserdata& pointer)
    {
        LuaUserdata* p = reinterpret_cast<LuaUserdata*>(lua_newuserdatauv(m_L, sizeof(LuaUserdata), 0));
        p->Pointer = pointer.Pointer;
        p->Owned = pointer.Owned;
    }

    // get integer from stack at index
    int64_t LuaStateImp::GetInteger(int position)
    {
        ASENGINE_ASSERT(lua_isinteger(m_L, position), "Type error");
        return lua_tointeger(m_L, position);
    }

    // get number from stack at index
    double LuaStateImp::GetNumber(int position)
    {
        ASENGINE_ASSERT(lua_isnumber(m_L, position), "Type error");
        return lua_tonumber(m_L, position);
    }

    // get string
    std::string LuaStateImp::GetString(int position)
    {
        ASENGINE_ASSERT(lua_isstring(m_L, position), "Type error");
        return std::string(lua_tostring(m_L, position));
    }

    // get boolean
    bool LuaStateImp::GetBoolean(int position)
    {
        ASENGINE_ASSERT(lua_isboolean(m_L, position), "Type error");
        return lua_toboolean(m_L, position);
    }

    // get userdata
    void LuaStateImp::GetUserdata(int position, LuaUserdata& pointer)
    {
        ASENGINE_ASSERT(lua_isuserdata(m_L, position), "Type error");
        LuaUserdata* p = reinterpret_cast<LuaUserdata*>(lua_touserdata(m_L, position));

        pointer.Pointer = p->Pointer;
        pointer.Owned = p->Owned;
    }

    void LuaStateImp::AddFunctions(const std::vector<LuaCppFunction>& funcitons)
    {
        for (const auto& function: funcitons)
        {
            AddFunction(function);
        }
    }

    void LuaStateImp::AddFunction(const LuaCppFunction& function)
    {
        lua_pushstring(m_L, function.Name.GetString().c_str());
        lua_pushlightuserdata(m_L, const_cast<LuaCppFunction::FunctionType*>(function.Function.get()));

        // set std::function as callable in lua
        lua_createtable(m_L, 0, 1);

        luaL_Reg funcs[] = {
            {"__call", &LuaStateImp::CallCppFunction},
            {nullptr, nullptr}
        };
        luaL_setfuncs(m_L, funcs, 0);
        lua_setmetatable(m_L, -2);

        // add this user data to the table
        lua_settable(m_L, -3);
    }

    void LuaStateImp::CreateLibrary(const std::string& libraryName, const std::vector<LuaCppFunction>& funcitons)
    {
        luaL_checkversion_(m_L, 504, (sizeof(lua_Integer) * 16 + sizeof(lua_Number)));
        lua_createtable(m_L, 0, funcitons.size());

        AddFunctions(funcitons);

        lua_setglobal(m_L, libraryName.c_str());
    }

    void LuaStateImp::CreateMetatable(const std::string& name, const std::string& parentName, const std::vector<LuaCppFunction>& funcitons)
    {
        // create metatableC
        lua_newtable(m_L);
        lua_pushstring(m_L, "__index");
        if (parentName == "")
        {
            lua_pushvalue(m_L, -2);
        }
        else
        {
            lua_getglobal(m_L, parentName.c_str());
        }
        lua_settable(m_L, -3);  /* metatable.__index = metatable */

        // add functions to metatable
        AddFunctions(funcitons);
        lua_setglobal(m_L, name.c_str());
    }

    void LuaStateImp::SetMetatable(const std::string& name)
    {
        lua_getglobal(m_L, name.c_str());
        lua_setmetatable(m_L, -2);
    }
}
