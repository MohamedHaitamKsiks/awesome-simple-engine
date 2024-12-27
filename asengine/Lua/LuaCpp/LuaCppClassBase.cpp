#include "LuaCppClassBase.h"

#include "LuaCppFunction.h"

#include "Core/String/UniqueString.h"

namespace ASEngine
{
    LuaCppClassBase::LuaCppClassBase(UniqueString className, UniqueString parentClassName)
    {
        m_ClassName = className;
        m_MetatableName = UniqueString("metatable__" + className.GetString());
        m_ParentClassName = parentClassName;
    }

    void LuaCppClassBase::BindBaseMethod(UniqueString methodName, LuaCppFunction::FunctionType method, bool isStatic)
    {
        MethodBinding& binding = m_MethodBindings[methodName];

        binding.IsStatic = isStatic;
        binding.Method.Name = methodName;
        binding.Method.Function = std::make_shared<LuaCppFunction::FunctionType>(method);
    }

}
