#ifndef __ASENGINE_LUA_CPP_CLASS_H
#define __ASENGINE_LUA_CPP_CLASS_H

#include "Class/ClassManager.h"

#include "Core/Error/Assertion.h"
#include "Core/String/UniqueString.h"

#include "LuaScript/LuaCppClassBuilder.h"
#include "LuaScript/LuaPointer.h"
#include "LuaScript/LuaState.h"
#include "LuaScriptManager.h"
#include "LuaScript/LuaCppClassManager.h"

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

// bind static method in binding area. camel cased
#define ASENGINE_BIND_STATIC_METHOD(method) \
    __luaCppClass->BindStaticMethod(#method, &__luaCppClassType::method)


namespace ASEngine
{
    // works with normal classes, resource classes
    template <typename T>
    class LuaCppClass: public LuaCppClassBuilder
    {
    public:
        LuaCppClass(UniqueString name): LuaCppClass(name, UniqueString{}) {}

        LuaCppClass(UniqueString name, UniqueString parentName): LuaCppClassBuilder(name, parentName)
        {
            ClassManager::GetInstance().RegisterClassIfNotRegisteredYet<T>(name);

            // if is resource bind some default static methods
            if constexpr (std::is_base_of_v<Resource, T>)
            {
                // bind constructor
                BindStaticMethod("new", []() -> ResourceRef<T>
                {
                    return T::GetResourceClass().New();
                });

                // bind load
                BindStaticMethod("load", []() -> ResourceRef<T>
                {
                    // return T::GetResourceClass()Load();
                });
            }

            // bind default methods
            // bind a cast method to anything
            // BindMethod("castTo", [](T* self) -> )

            // bind destructor
            BindBaseMethod("__gc",  []() -> int
            {
                using DestroyType = std::conditional_t<std::is_base_of_v<Resource, T>, ResourceRef<T>, T>;

                auto& state = LuaScriptManager::GetInstance().GetState();
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
                auto& state = LuaScriptManager::GetInstance().GetState();
                auto createUserdata = [&state](Args... args)
                {
                    state.CreateUserdata<T, Args...>(args...);
                };

                if constexpr(sizeof...(Args) == 0)
                {
                    createUserdata();
                }
                else
                {
                    auto arguments = GetArguments<Args...>(state);
                    std::apply(createUserdata, arguments);
                }

                return 1;
            }, true);
        }

        template<typename ReturnType, typename... Args>
        void BindMethod(const std::string& methodName, ReturnType (T::*method)(Args...))
        {
            using SelfPointer = std::conditional_t<std::is_base_of_v<Resource, T>, ResourceRef<T>&, T*>;

            std::function<ReturnType(SelfPointer, Args...)> methodLambda = [method](SelfPointer self, Args... args) -> ReturnType
            {
                return (self ->* method)(args...);
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
            return GetArugmentsImp<Args...>(state, std::index_sequence_for<Args...>{});
        }

        // bind mefuncthod
        template<typename ReturnType, typename... Args>
        void BindAnyMethod(std::string methodName, std::function<ReturnType(Args...)> method, bool isStatic)
        {
            methodName[0] = std::tolower(methodName[0]); // force camel case

            auto baseMethodLambda = [method]() -> int
            {
                LuaState& state = LuaScriptManager::GetInstance().GetState();
                constexpr bool hasArguments = sizeof...(Args);

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
                        state.Push(result);
                    }
                    else
                    {
                       ReturnType result = method();
                       state.Push(result);
                    }
                    return 1;
                }
            };

            BindBaseMethod(methodName, baseMethodLambda, isStatic);
        }

    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_CPP_CLASS_H
