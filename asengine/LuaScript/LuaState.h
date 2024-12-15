#ifndef __ASENGINE_LUA_VIRTUAL_MACHINE_H
#define __ASENGINE_LUA_VIRTUAL_MACHINE_H

#include "Class/Class.h"
#include "Core/Error/Assertion.h"
#include "LuaScript/LuaCppClassManager.h"
#include "LuaScript/LuaCppFunction.h"
#include "LuaScript/LuaPointer.h"
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

        // create lua metatable from functions
        virtual void CreateMetatable(const std::string& name, const std::string& parentName, const std::vector<LuaCppFunction>& funcitons) = 0;

        // create userdata and push it to the stack
        template <typename T, typename... Args>
        void CreateUserdata(Args... args)
        {
            LuaPointer newUserData{};
            newUserData.Pointer = reinterpret_cast<void*>(new T(args...));
            newUserData.Owned = true;

            PushPointer(newUserData);

            auto& luaCppClassManager = LuaCppClassManager::GetInstance();

            using MetatableType = std::conditional_t<IsResourceRef<T>::value, RemoveResourceRefType<T>, T>;
            UniqueString metatableName = luaCppClassManager.GetMetatableName<MetatableType>();

            SetMetatable(metatableName.GetString());
        }

        // destroy userdata from the stack
        template <typename T>
        void DeleteUserdata(int position)
        {
            LuaPointer luaPointer{};
            GetPointer(1, luaPointer);

            if (!luaPointer.Owned)
                return;

            T* p = reinterpret_cast<T*>(luaPointer.Pointer);
            ASENGINE_ASSERT(p, "Destructor pointer invalid type");

            delete p;
            p = nullptr;
        }

        // set metatable for the current top of the stack
        virtual void SetMetatable(const std::string& name) = 0;

        // create library
        virtual void CreateLibrary(const std::string& libraryName, const std::vector<LuaCppFunction>& funcitons) = 0;

        // run string as lua script
        virtual void Run(const std::string& script) = 0;

        // push something to the stack
        // integers numbers booleans and strings are pushed by value
        // when pushing a reference / pointer to a userdata you pass a non owned pointer
        // when pushing a value it should be copyable so that it creates an owned copy
        template <typename T>
        void Push(T t)
        {
            // push integer
            if constexpr(std::is_integral_v<T>)
            {
                PushInteger(static_cast<int64_t>(t));
            }
            // push numbers
            else if constexpr(std::is_floating_point_v<T>)
            {
                PushNumber(static_cast<double>(t));
            }
            // push string
            else if constexpr(std::is_same_v<std::decay_t<T>, std::string>)
            {
                PushString(t);
            }
            // user data case
            else
            {
                LuaPointer p{};

                auto& luaCppClassManager = LuaCppClassManager::GetInstance();
                using UserdataType = ClassType<T>;
                using MetatableType = std::conditional_t<IsResourceRef<UserdataType>::value, RemoveResourceRefType<UserdataType>, UserdataType>;

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

                UniqueString metatableName = luaCppClassManager.GetMetatableName<MetatableType>();

                PushPointer(p);
                SetMetatable(metatableName.GetString());
            }
        }

        // get value from the stack
        template <typename T>
        T Get(int position)
        {
            using UserdataType = ClassType<T>;

            // push integer
            if constexpr(std::is_integral_v<UserdataType>)
            {
                return GetInteger(position);
            }
            // push numbers
            else if constexpr(std::is_floating_point_v<UserdataType>)
            {
                return GetNumber(position);
            }
            // push string
            else if constexpr(std::is_same_v<UserdataType, std::string>)
            {
                return GetString(position);
            }
            // user data case
            else
            {
                LuaPointer p{};
                GetPointer(position, p);

                UserdataType* t = reinterpret_cast<UserdataType*>(p.Pointer);

                // return reference to user data
                if constexpr (std::is_reference_v<T>)
                {
                    return *t;
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
        ReturnType Call(const std::string& functionName, Args... args)
        {
            constexpr size_t argsCount = sizeof...(args);
            PushArguments(args...);

            constexpr bool doesReturn = !std::is_void_v<ReturnType>;

            CallFunction(functionName, argsCount, doesReturn);

            if constexpr (doesReturn)
                return Get<ReturnType>(-1);
        }

    protected:
        template <typename T>
        using ClassType = std::remove_pointer_t<std::decay_t<T>>;

        friend class LuaCppClassBuilder;
        template <typename T>friend class LuaCppClass;

        // push arguments
        template <typename T, typename... types>
        void PushArguments(T firstArgument, types... args)
        {
            Push(firstArgument);

            if constexpr(sizeof...(args) > 0)
                PushArguments(args...);
        }

        // call function by name
        virtual void CallFunction(const std::string& functionName, int argumentsCount, bool doesReturn) = 0;

        // push integer to the stack
        virtual void PushInteger(int64_t integer) = 0;

        // push number to the stack
        virtual void PushNumber(double number) = 0;

        // push string
        virtual void PushString(const std::string &str) = 0;

        // push boolean
        virtual void PushBoolean(bool value) = 0;

        // push a pointer to userdata
        virtual void PushPointer(const LuaPointer& pointer) = 0;

        // get integer from stack at index
        virtual int64_t GetInteger(int position) = 0;

        // get number from stack at index
        virtual double GetNumber(int position) = 0;

        // get string
        virtual std::string GetString(int position) = 0;

        // get boolean
        virtual bool GetBoolean(int position) = 0;

        // get userdata
        virtual void GetPointer(int position, LuaPointer& pointer) = 0;
    };
} // ASEngine

#endif // __ASENGINE_LUA_VIRTUAL_MACHINE_H
