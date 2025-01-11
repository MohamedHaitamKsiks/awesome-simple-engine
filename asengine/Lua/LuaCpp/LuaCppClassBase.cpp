#include "LuaCppClassBase.h"

namespace ASEngine
{
    LuaCppClassBase::LuaCppClassBase(UniqueString className, UniqueString parentClassName): LuaCppType(className)
    {
        m_ParentClassName = parentClassName;
    }

    std::unordered_map<std::string, LuaCppFunction> LuaCppClassBase::GetMethods() const
    {
        std::unordered_map<std::string, LuaCppFunction> methods{};
        for (const auto& [name, methodBinding]: m_MethodBindings)
        {
            if (!methodBinding.IsStatic)
                methods[name] = methodBinding.Method;   
        }

        return methods;
    }

    std::unordered_map<std::string, LuaCppFunction> LuaCppClassBase::GetStaticMethods() const
    {
        std::unordered_map<std::string, LuaCppFunction> staticMethods{};
        for (const auto &[name, methodBinding] : m_MethodBindings)
        {
            if (methodBinding.IsStatic)
                staticMethods[name] = methodBinding.Method;
        }

        return staticMethods;
    }

    void LuaCppClassBase::BindCppFunction(const std::string& methodName, LuaCppFunction method, bool isStatic)
    {
        ASENGINE_ASSERT(m_MethodBindings.find(methodName) == m_MethodBindings.end(), "method already bound");

        MethodBinding& binding = m_MethodBindings[methodName];

        binding.IsStatic = isStatic;
        binding.Method = method;
    }

}
