#ifndef __ASENGINE_LUA_VIRTUAL_MACHINE_H
#define __ASENGINE_LUA_VIRTUAL_MACHINE_H

#include "Class/Class.h"

#include "Core/Error/Assertion.h"

#include "Lua/LuaTypes/LuaUserdata.h"
#include "Lua/LuaTypes/LuaTypes.h"

#include "Lua/LuaCpp/LuaCppClassBase.h"
#include "Lua/LuaCpp/LuaCppEnum.h"
#include "Lua/LuaCpp/LuaCppCleanupArgs.h"

#include "Resource/ResourceRef.h"

#include <cstdint>
#include <functional>
#include <string>
#include <cinttypes>
#include <type_traits>
#include <vector>

namespace ASEngine
{
    // warper build on lua state
    // made for two reasons
    // reduce the amount of code necessary
    // hide the lua c api from the user
    class LuaState
    {
    public:
        LuaState() {}
        virtual ~LuaState() {}

        // prohibit copy & assignement
        LuaState(const LuaState& luaState) = delete;
        LuaState& operator=(const LuaState& luaState) = delete;

        // create userdata and push it to the stack
        template <typename T, typename... Args>
        void CreateUserdata(Args... args)
        {
            using MetatableType = std::conditional_t<IsResourceRef<T>::value,
                RemoveResourceRefType<T>,
                T>;

            LuaUserdata newUserData{};

            newUserData.Pointer = reinterpret_cast<void*>(new T(args...));
            newUserData.Owned = true;
            newUserData.Name = Class<MetatableType>::GetName();

            PushUserdata(newUserData);
        }

        // destroy userdata from the stack
        template <typename T>
        void DeleteUserdata(int position)
        {
            LuaUserdata luaPointer{};
            GetUserdata(1, luaPointer);

            if (!luaPointer.Owned)
                return;

            T* p = reinterpret_cast<T*>(luaPointer.Pointer);
            ASENGINE_ASSERT(p, "Cannot destroy nullptr!");

            delete p;
            p = nullptr;
        }


        // run string as lua script
        virtual void Run(const std::string& script) = 0;

        // push something to the stack
        // integers numbers booleans and strings are pushed by value
        // when pushing a reference / pointer to a userdata you pass a non owned pointer
        // when pushing a value it should be copyable so that it creates an owned copy
        template <typename T>
        void Push(T t)
        {
            using UserdataType = ClassType<T>;

            // push integer
            if constexpr (std::is_integral_v<UserdataType>)
            {
                PushInteger(static_cast<int64_t>(t));
            }
            // push numbers
            else if constexpr (std::is_floating_point_v<UserdataType>)
            {
                PushNumber(static_cast<double>(t));
            }
            // push string
            else if constexpr (std::is_same_v<UserdataType, std::string>)
            {
                PushString(t);
            }
            // push unique string as string
            else if constexpr (std::is_same_v<UserdataType, UniqueString>)
            {
                PushString(t.GetString());
            }
            // user data case
            else
            {
                LuaUserdata p{};

                using MetatableType = std::conditional_t<IsResourceRef<UserdataType>::value, 
                    RemoveResourceRefType<UserdataType>, 
                    UserdataType>;

                p.Name = Class<MetatableType>::GetName();

                // push reference to user data
                if constexpr(std::is_reference_v<T>)
                {
                    p.Pointer = reinterpret_cast<void*>(&t);
                    p.Owned = false;
                }
                // push pointer
                else if constexpr(std::is_pointer_v<T>)
                {
                    p.Pointer = reinterpret_cast<void*>(t);
                    p.Owned = false;
                }
                // push value of user data
                else
                {
                    p.Pointer = reinterpret_cast<void*>(new UserdataType(t)); // push copy
                    p.Owned = true;
                }

                PushUserdata(p);
            }
        }

        // get value from the stack
        template <typename T>
        T Get(int position)
        {
            using UserdataType = ClassType<T>;

            // push integer
            if constexpr (std::is_integral_v<UserdataType>)
            {
                return GetInteger(position);
            }
            // push numbers
            else if constexpr (std::is_floating_point_v<UserdataType>)
            {
                return GetNumber(position);
            }
            // push string
            else if constexpr (std::is_same_v<UserdataType, std::string>)
            {
                return GetString(position);
            }
            // get unique string as string
            else if constexpr (std::is_same_v<UserdataType, UniqueString>)
            {
                return UniqueString(GetString(position));
            }
            // user data case
            else
            {   
                LuaUserdata p{};
                GetUserdata(position, p);

                UserdataType* t = reinterpret_cast<UserdataType*>(p.Pointer);

                // return reference to user data
                if constexpr (std::is_reference_v<T>)
                {
                    UserdataType& ref= *t;
                    return ref;
                }
                // return pointer
                else if constexpr (std::is_pointer_v<T>)
                {
                    return t;
                }
                // return value of user data
                else
                {
                    return T(*t); // return copy
                }
            }
        }

        // call function by name
        // only global functions with no returns since this is all we need
        template<typename ReturnType, typename... Args>
        ReturnType Call(int position, Args... args)
        {
            constexpr size_t argsCount = sizeof...(args);
            PushArguments(args...);

            constexpr bool doesReturn = !std::is_void_v<ReturnType>;

            CallFunction(position, argsCount, doesReturn);

            if constexpr (doesReturn)
                return Get<ReturnType>(-1);
        }

        // create lua cpp function from any function
        template <typename ReturnType, typename... Args>
        static LuaCppFunction CreateLuaCppFunction(std::function<ReturnType(Args...)> func)
        {
            auto luaCppFunction = [func](LuaState& state) -> int
            {
                constexpr bool hasArguments = sizeof...(Args) > 0;

                if constexpr (std::is_void_v<ReturnType>)
                {
                    if constexpr (hasArguments)
                    {
                        auto arguments = state.GetArguments<Args...>();
                        std::apply(func, arguments);
                    }
                    else
                    {
                        func();
                    }
                    return 0;
                }
                else
                {
                    if constexpr (hasArguments)
                    {
                        auto arguments = state.GetArguments<Args...>();
                        ReturnType result = std::apply(func, arguments);
                        state.Push<ReturnType>(result);
                    }
                    else
                    {
                        ReturnType result = func();
                        state.Push<ReturnType>(result);
                    }
                    return 1;
                }
            };

            return LuaCppFunction(luaCppFunction);
        }

        template <typename... Args>
        auto GetArguments()
        {
            return GetArugmentsImp<LuaCppCleanupArgT<Args>...>(std::index_sequence_for<Args...>{});
        }

        // add cpp class and return metatable
        virtual LuaInteger AddLuaCppClass(const LuaCppClassBase& luaCppClass) = 0;

        // add cpp enum 
        virtual void AddLuaCppEnum(const LuaCppEnum& luaCppEnum) = 0;


    protected:
        template <typename T>
        using ClassType = std::remove_cv_t <std::remove_pointer_t<std::decay_t<T>>>;

        friend class LuaCppClassBase;
        template <typename T>friend class LuaCppClass;

        // push arguments
        template <typename T, typename... types>
        void PushArguments(T firstArgument, types... args)
        {
            Push<T>(firstArgument);

            if constexpr(sizeof...(args) > 0)
                PushArguments(args...);
        }
        
        // get arguments
        template <typename... Args, std::size_t... Indices>
        auto GetArugmentsImp(std::index_sequence<Indices...>)
        {
            auto argIndices = std::make_index_sequence<sizeof...(Args)>{};
            return std::tuple<Args...>(Get<Args>(static_cast<int>(Indices) - static_cast<int>(sizeof...(Args)))...);
        }

        // call function in the stack
        virtual void CallFunction(int position, int argumentsCount, bool doesReturn) = 0;

        // push integer to the stack
        virtual void PushInteger(int64_t integer) = 0;

        // push number to the stack
        virtual void PushNumber(double number) = 0;

        // push string
        virtual void PushString(const std::string &str) = 0;

        // push boolean
        virtual void PushBoolean(bool value) = 0;

        // push a pointer to userdata
        virtual void PushUserdata(const LuaUserdata& pointer) = 0;

        // get integer from stack at index
        virtual int64_t GetInteger(int position) = 0;

        // get number from stack at index
        virtual double GetNumber(int position) = 0;

        // get string
        virtual std::string GetString(int position) = 0;

        // get boolean
        virtual bool GetBoolean(int position) = 0;

        // get userdata
        virtual void GetUserdata(int position, LuaUserdata& pointer) = 0;
    };
} // ASEngine

#endif // __ASENGINE_LUA_VIRTUAL_MACHINE_H
