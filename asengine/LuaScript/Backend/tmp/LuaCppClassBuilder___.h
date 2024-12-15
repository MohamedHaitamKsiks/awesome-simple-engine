/*#ifndef __ASENGINE_LUA_CPP_CLASS_BUILDER_H
#define __ASENGINE_LUA_CPP_CLASS_BUILDER_H

#include "LuaScript/LuaCppFunction.h"
#include "LuaScript/LuaPointer.h"
#include "LuaScript/LuaState.h"
#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

namespace ASEngine
{
    // to build a c++ class binding to lua
    // just a data structure with no logic
    class LuaCppClassBuilder
    {
    public:
        struct MethodBinding
        {
            LuaCppFunction Method;
            bool IsStatic = false;
        };

        LuaCppClassBuilder(const std::string& className);
        ~LuaCppClassBuilder() {};

        // set class with a constructor
        template<typename Type, typename... Args>
        void InitClass()
        {
            std::string metatableName = m_MetatableName;

            // bind constructor
            BindStaticMethod("new", [metatableName] (LuaState& state, Args... args)
            {
                state.CreateUserdata<Type>(args...);
                state.SetMetatable(metatableName);
            });

            // bind destructor
            BindMethod("__gc", [](LuaState& state)
            {
                LuaPointer p{};
                state.GetPointer(1, p);

                // delete if owned
                if (p.Owned)
                    delete reinterpret_cast<Type*>(p.Pointer);
            });
        }

        template<typename Type, typename ReturnType, typename... Args>
        void BindMethod(const std::string& methodName, ReturnType (Type::*method)(Args...))
        {
            BindAnyMethod(methodName, [method](Type* self, Args... args) -> ReturnType
            {
                return (self ->* method)(args...);
            }, false);
        }

        template<typename Type,typename ReturnType, typename... Args>
        inline void BindStaticMethod(const std::string& methodName, ReturnType (Type::*method)(Args...))
        {
            BindAnyMethod(methodName, method, true);
        }


    protected:
        // get arguments
        template<typename... Args>
        static auto GetArugments(LuaState& state)
        {
            auto argIndices = std::make_index_sequence<sizeof...(Args)>{};
            return std::make_tuple(state.Get<Args>(argIndices + 1)...);
        }

        // bind mefuncthod
        template<typename ReturnType, typename... Args>
        void BindMethod(const std::string& methodName, ReturnType (*method)(Args...), bool isStatic)
        {
            BindMethod(methodName, [method](void*) -> int
            {
                LuaState& state = LuaScriptManager::GetInstance().GetState();
                auto arguments = GetArugments<Args...>(state);
                if constexpr(std::is_void_v<ReturnType>)
                {
                    std::apply(method, arguments);
                    return 0;
                }
                else
                {
                    auto result = std::apply(method, arguments);
                    state.Push(result);
                    return 1;
                }

            }, isStatic);
        }


    private:
        std::string m_ClassName = "";
        std::string m_MetatableName = ""; // unique and generated from the class name

        std::unordered_map<std::string, MethodBinding> m_MethodBindings{};

        // bind method as function
        void BindMethod(const std::string& methodName, int (*method)(void*), bool isStatic = false);

    };
} // namespace ASEngine

#endif // __ASENGINE_LUA_CPP_CLASS_BUILDER_H
*/
