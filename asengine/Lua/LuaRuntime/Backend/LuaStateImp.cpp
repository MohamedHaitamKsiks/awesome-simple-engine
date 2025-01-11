#include "LuaStateImp.h"

#include "Core/Error/Assertion.h"

#include "Lua/LuaRuntime/LuaRuntime.h"
#include "Lua/LuaTypes/LuaUserdata.h"
#include "Lua/LuaCpp/LuaCppTypeManager.h"

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

        // collect garbage
        result = lua_gc(m_L, LUA_GCCOLLECT);
        __ASENGINE_LUA_ASSERT(result);
    }

    int LuaStateImp::CallCppFunction(lua_State* L)
    {
        ASENGINE_ASSERT(lua_isuserdata(L, lua_upvalueindex(1)), "Type Error");

        LuaCppFunction &fun = *reinterpret_cast<LuaCppFunction *>(
            lua_touserdata(L, lua_upvalueindex(1))
        );

        LuaState& state = LuaRuntime::GetInstance().GetState();
        return fun(state);
    }

    int LuaStateImp::DestroyCppFunction(lua_State *L)
    {
        ASENGINE_ASSERT(lua_isuserdata(L, 1), "Type Error");

        LuaCppFunction* pFunc = reinterpret_cast<LuaCppFunction*>(lua_touserdata(L, 1));
        std::destroy_at(pFunc);

        return 0;
    }

    LuaInteger LuaStateImp::AddLuaCppClass(const LuaCppClassBase &luaCppClass)
    {
        // create library with static methods
        auto staticMethods = luaCppClass.GetStaticMethods();
        const char* className = luaCppClass.GetName().GetString().c_str();

        lua_createtable(m_L, 0, staticMethods.size());

        /*lua_pushstring(m_L, "__index");
        lua_pushvalue(m_L, -2);
        lua_settable(m_L, -3);
        */
        for (auto& [name, staticMethod]: staticMethods)
        {
            AddFunction(name, staticMethod);
        }

        lua_setglobal(m_L, className);

        // create metatable with methods
        auto methods = luaCppClass.GetMethods();
        lua_createtable(m_L, 0, methods.size());

        // set __index
        UniqueString parentName = luaCppClass.GetParentName();
        
        lua_pushstring(m_L, "__index");
        lua_pushvalue(m_L, -2);
        lua_settable(m_L, -3);
        
        if (parentName.GetID() != UNIQUE_STRING_ID_NULL)
        {
            lua_Integer parentMetatableID = LuaCppTypeManager::GetInstance().GetMetatableID(parentName);
            lua_rawgeti(m_L, LUA_REGISTRYINDEX, parentMetatableID);
        
            lua_pushnil(m_L);
            while (lua_next(m_L, -2) != 0)
            {
                lua_pushvalue(m_L, -2);
                lua_insert(m_L, -2);
                lua_settable(m_L, -4);
            }
        }

        for (auto &[name, method] : methods)
        {
            AddFunction(name, method);
        }

       // create and return reference
       lua_Integer metatableID = luaL_ref(m_L, LUA_REGISTRYINDEX);
        
        // for singleton set table name to instance
        void* pSingleton = luaCppClass.GetSingleton();
        if (pSingleton)
        {
            // push singleton as reference => not owned by lua
            LuaUserdata *p = reinterpret_cast<LuaUserdata *>(lua_newuserdatauv(m_L, sizeof(LuaUserdata), 0));
            p->Pointer = pSingleton;
            p->Owned = false;
            p->Name = luaCppClass.GetName();

            // get metatable and set it to singleton
            lua_rawgeti(m_L, LUA_REGISTRYINDEX, metatableID);
            lua_setmetatable(m_L, -2);
            
            // set class table as singleton
            lua_setglobal(m_L, className);
        }
       
       return metatableID;
   }

   void LuaStateImp::AddLuaCppEnum(const LuaCppEnum &luaCppEnum)
   {
        const auto& values = luaCppEnum.GetValues();
        const char* enumName = luaCppEnum.GetName().GetString().c_str();

        // create table with keys as enum names
        lua_createtable(m_L, 0, values.size());

        for (auto& [name, value]: values)
        {
            lua_pushstring(m_L, name.c_str());
            lua_pushinteger(m_L, value);
            lua_settable(m_L, -3);
        }

        lua_setglobal(m_L, enumName);
   }

   // call function by name
   void LuaStateImp::CallFunction(int position, int argumentsCount, bool doesReturn)
   {
       ASENGINE_ASSERT(lua_isfunction(m_L, position), "Type Error");

       lua_insert(m_L, position);

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
       p->Name = pointer.Name;

       // set metatable
       LuaInteger metatableID = LuaCppTypeManager::GetInstance().GetMetatableID(pointer.Name);

       lua_rawgeti(m_L, LUA_REGISTRYINDEX, metatableID);
       lua_setmetatable(m_L, -2);
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

   void LuaStateImp::PushFunction(LuaCppFunction func)
   {
       LuaCppFunction* pFunc = reinterpret_cast<LuaCppFunction*>(lua_newuserdata(m_L, sizeof(LuaCppFunction)));
       std::construct_at(pFunc, func);

       lua_createtable(m_L, 0, 2);
       luaL_Reg funcs[] = {
           {"__gc", &LuaStateImp::DestroyCppFunction},
           {nullptr, nullptr}
       };
       luaL_setfuncs(m_L, funcs, 0);
       lua_setmetatable(m_L, -2);

       lua_pushcclosure(m_L, &LuaStateImp::CallCppFunction, 1);
   }

   void LuaStateImp::AddFunction(const std::string& name, LuaCppFunction function)
   {
       lua_pushstring(m_L, name.c_str());
       PushFunction(function);
       // add this user data to the table
       lua_settable(m_L, -3);
   }

}
