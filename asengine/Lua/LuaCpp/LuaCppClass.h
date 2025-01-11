#ifndef __ASENGINE_LUA_CPP_CLASS_H
#define __ASENGINE_LUA_CPP_CLASS_H

#include "Class/ClassManager.h"

#include "Core/Error/Assertion.h"
#include "Core/String/UniqueString.h"

#include "Lua/LuaRuntime/LuaRuntime.h"
#include "Lua/LuaRuntime/LuaState.h"

#include "Lua/LuaTypes/LuaUserdata.h"

#include "LuaCppClassBase.h"
#include "LuaCppTypeManager.h"
#include "LuaCppCleanupArgs.h"

#include "Resource/Resource.h"
#include "Resource/ResourceRef.h"

#include <cctype>
#include <type_traits>

// begin binding area, you can NOT begin a binding area inside another binding area
#define ASENGINE_LUA_CPP_CLASS_BEGIN(classToBind) { \
    using __luaCppClassType = classToBind; \
    ASEngine::LuaCppClass<classToBind> __luaCppClass(#classToBind);

// begin binding area ofr derived class
#define ASENGINE_LUA_CPP_CLASS_DERIVED_BEGIN(classToBind, parentClass) { \
    ASEngine::LuaCppClass<classToBind> __luaCppClass(#classToBind, #parentClass);

// end binding area
#define ASENGINE_LUA_CPP_CLASS_END() \
    ASEngine::LuaCppTypeManager::GetInstance().RegisterLuaCppClass(__luaCppClass); }

// bind constructor as new
#define BIND_CONSTRUCTOR(...) \
    __luaCppClass.BindConstructor<__VA_ARGS__>()

// bind method in binding area. camel cased
#define BIND_METHOD(methodName, method) \
    __luaCppClass.BindMethod(methodName, &__luaCppClassType::method)

// bind method in binding area. camel cased
#define BIND_METHOD_EXT(methodName, method, ...) \
    __luaCppClass.BindMethod<__VA_ARGS__>(methodName, &__luaCppClassType::method)

// bind static method in binding area. camel cased
#define BIND_STATIC_METHOD(methodName, method) \
    __luaCppClass.BindStaticMethod(methodName, &__luaCppClassType::method)

// bind static method in binding area. camel cased
#define BIND_STATIC_METHOD_EXT(methodName, method, ...) \
    __luaCppClass.BindStaticMethod<__VA_ARGS__>(methodName, &__luaCppClassType::method)

// bind any function
#define BIND_FUNCTION(functionName, func, isStatic) \
    __luaCppClass.BindFunction(functionName, std::function(func), isStatic)

// set singleton
#define SET_SINGLETON() \
    __luaCppClass.SetSingleton(__luaCppClassType::GetInstance())

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

            // bind get class name
            BindStaticMethod("get_class_name", [name]() -> UniqueString
            {
                return name;
            });

            // bind destructor
            BindCppFunction("__gc",  [](LuaState& state) -> int
            {
                using DestroyType = std::conditional_t<std::is_base_of_v<Resource, T>, ResourceRef<T>, T>;
                state.DeleteUserdata<DestroyType>(1);
                
                return 0;
            }, false);
        }

        ~LuaCppClass() {}

        template<typename FunctionType>
        inline void BindStaticMethod(const std::string& methodName, FunctionType method)
        {
            BindFunction(methodName, std::function(method), true);
        }

        template<typename... Args>
        inline void BindConstructor()
        {
            BindCppFunction("new", [](LuaState& state) -> int
            {
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
                auto arguments = state.GetArguments<Args...>();
                std::apply(createUserdata, arguments);
            
                return 1;
            }, true);
        }

        template<typename ReturnType, typename... Args>
        inline void BindMethod(const std::string& methodName, ReturnType (T::*method)(Args...))
        {
            BindTypedMethod<ReturnType, Args...>(methodName, method);
        }

        template <typename ReturnType, typename... Args>
        inline void BindMethod(const std::string &methodName, ReturnType (T::*method)(Args...) const)
        {
            BindTypedMethod<ReturnType, Args...>(methodName, method);
        }

        // bind functhod
        template<typename ReturnType, typename... Args>
        inline void BindFunction(std::string methodName, std::function<ReturnType(Args...)> method, bool isStatic)
        {
            auto baseMethodLambda = LuaState::CreateLuaCppFunction(method);
            BindCppFunction(methodName, baseMethodLambda, isStatic);
        }

    private:
        template <typename ReturnType, typename... Args, typename MethodType>
        inline void BindTypedMethod(const std::string &methodName, MethodType method)
        {
            using SelfPointer = std::conditional_t<std::is_base_of_v<Resource, T>, ResourceRef<T> &, T *>;

            auto methodLambda = [method](SelfPointer self, Args... args) -> ReturnType
            {
                return ((*self).*method)(args...);
            };

            BindFunction(methodName, std::function(methodLambda), false);
        }
    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_CPP_CLASS_H
