#ifndef __ASENGINE_LUA_CPP_CLASS_H
#define __ASENGINE_LUA_CPP_CLASS_H

#include "Class/ClassManager.h"

#include "Core/Error/Assertion.h"
#include "Core/String/UniqueString.h"

#include "Lua/LuaRuntime/LuaRuntime.h"
#include "Lua/LuaRuntime/LuaState.h"

#include "Lua/LuaTypes/LuaUserdata.h"

#include "LuaCppClassBase.h"
#include "LuaCppClassManager.h"
#include "LuaCppCleanupArgs.h"

#include "Resource/Resource.h"
#include "Resource/ResourceRef.h"

#include <cctype>
#include <type_traits>

// begin binding area, you can NOT begin a binding area inside another binding area
#define ASENGINE_LUA_CPP_CLASS_BEGIN(classToBind) { \
    using __luaCppClassType = classToBind; \
    auto __luaCppClass = std::make_unique<ASEngine::LuaCppClass<classToBind>>(#classToBind);

// begin binding area ofr derived class
#define ASENGINE_LUA_CPP_CLASS_DERIVED_BEGIN(classToBind, parentClass) { \
    auto __luaCppClass = std::make_unique<ASEngine::LuaCppClass<classToBind>>(#classToBind, #parentClass);

// end binding area
#define ASENGINE_LUA_CPP_CLASS_END() \
    ASEngine::LuaCppClassManager::GetInstance().RegisterLuaCppClass(std::move(__luaCppClass)); }

// bind constructor as new
#define ASENGINE_BIND_CONSTRUCTOR(...) \
    __luaCppClass->BindConstructor<__VA_ARGS__>()


// bind method in binding area. camel cased
#define ASENGINE_BIND_METHOD(method) \
    __luaCppClass->BindMethod(#method, &__luaCppClassType::method)

// bind method in binding area. camel cased
#define ASENGINE_BIND_METHOD_EXT(method, ...) \
    __luaCppClass->BindMethod<__VA_ARGS__>(#method, &__luaCppClassType::method)

// bind static method in binding area. camel cased
#define ASENGINE_BIND_STATIC_METHOD(method) \
    __luaCppClass->BindStaticMethod(#method, &__luaCppClassType::method)

// bind static method in binding area. camel cased
#define ASENGINE_BIND_STATIC_METHOD_EXT(method, ...) \
    __luaCppClass->BindStaticMethod<__VA_ARGS__>(#method, &__luaCppClassType::method)

namespace ASEngine
{
    // works with normal classes, resource classes
    template <typename T>
    class LuaCppClass: public LuaCppClassBase
    {
    public:
        LuaCppClass(UniqueString name): LuaCppClass(name, UniqueString{}) {}

        LuaCppClass(UniqueString name, UniqueString parentName): LuaCppClassBase(name, parentName)
        {
            ClassManager::GetInstance().RegisterClassIfNotRegisteredYet<T>(name);

            // bind destructor
            BindBaseMethod("__gc",  []() -> int
            {
                using DestroyType = std::conditional_t<std::is_base_of_v<Resource, T>, ResourceRef<T>, T>;

                auto& state = LuaRuntime::GetInstance().GetState();
                state.DeleteUserdata<DestroyType>(1);

                return 0;
            }, false);
        }

        ~LuaCppClass() {}

        template<typename FunctionType>
        inline void BindStaticMethod(const std::string& methodName, FunctionType method)
        {
            BindAnyMethod(methodName, std::function(method), true);
        }

        template<typename... Args>
        inline void BindConstructor()
        {
            BindBaseMethod("new", []() -> int
            {
                auto& state = LuaRuntime::GetInstance().GetState();
                
                // construct resource class
                if constexpr (std::is_base_of_v<Resource, T>)
                {
                    ResourceRef<T> rref = T::GetResourceClass().New();
                    state.Push<ResourceRef<T>>(rref);
                    return 1;
                }

                // construct normal class
                auto createUserdata = [&state](Args... args)
                {
                    state.CreateUserdata<T, Args...>(args...);
                };

                // construct with no argumnent
                if constexpr(sizeof...(Args) == 0)
                {
                    createUserdata();
                    return 1;
                }

                // construct with many arguments
                auto arguments = GetArguments<Args...>(state);
                std::apply(createUserdata, arguments);
            
                return 1;
            }, true);
        }

        template<typename ReturnType, typename... Args>
        void BindMethod(const std::string& methodName, ReturnType (T::*method)(Args...))
        {
            using SelfPointer = std::conditional_t<std::is_base_of_v<Resource, T>, ResourceRef<T>&, T*>;

            std::function<ReturnType(SelfPointer, Args...)> methodLambda = [method](SelfPointer self, Args... args) -> ReturnType
            {
                return ((*self).* method)(args...);
            };

            BindAnyMethod(methodName, methodLambda, false);
        }

        template <typename ReturnType, typename... Args>
        void BindMethod(const std::string &methodName, ReturnType (T::*method)(Args...) const)
        {
            using SelfPointer = std::conditional_t<std::is_base_of_v<Resource, T>, ResourceRef<T> &, T *>;

            std::function<ReturnType(SelfPointer, Args...)> methodLambda = [method](SelfPointer self, Args... args) -> ReturnType
            {
                return ((*self).* method)(args...);
            };

            BindAnyMethod(methodName, methodLambda, false);
        }

    private:

        // get arguments
        template<typename... Args, std::size_t... Indices>
        static auto GetArugmentsImp(LuaState& state, std::index_sequence<Indices...>)
        {
            auto argIndices = std::make_index_sequence<sizeof...(Args)>{};
            return std::make_tuple(state.Get<Args>(Indices + 1)...);
        }

        template<typename... Args>
        static auto GetArguments(LuaState& state)
        {
            return GetArugmentsImp<LuaCppCleanupArgT<Args>...>(state, std::index_sequence_for<Args...>{});
        }

        // bind mefuncthod
        template<typename ReturnType, typename... Args>
        void BindAnyMethod(std::string methodName, std::function<ReturnType(Args...)> method, bool isStatic)
        {
            methodName[0] = std::tolower(methodName[0]); // force camel case

            auto baseMethodLambda = [method]() -> int
            {
                LuaState& state = LuaRuntime::GetInstance().GetState();
                constexpr bool hasArguments = sizeof...(Args) > 0;

                if constexpr(std::is_void_v<ReturnType>)
                {
                    if constexpr(hasArguments)
                    {
                        auto arguments = GetArguments<Args...>(state);
                        std::apply(method, arguments);
                    }
                    else
                    {
                        method();
                    }
                    return 0;
                }
                else
                {
                    if constexpr(hasArguments)
                    {
                        auto arguments = GetArguments<Args...>(state);
                        ReturnType result = std::apply(method, arguments);
                        state.Push<ReturnType>(result);
                    }
                    else
                    {
                       ReturnType result = method();
                       state.Push<ReturnType>(result);
                    }
                    return 1;
                }
            };

            BindBaseMethod(methodName, baseMethodLambda, isStatic);
        }

    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_CPP_CLASS_H
