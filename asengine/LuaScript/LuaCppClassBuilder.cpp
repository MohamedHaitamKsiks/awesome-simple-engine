#include "LuaCppClassBuilder.h"
#include "Core/String/UniqueString.h"

#include "LuaCppFunction.h"

namespace ASEngine
{
    LuaCppClassBuilder::LuaCppClassBuilder(UniqueString className, UniqueString parentClassName)
    {
        m_ClassName = className;
        m_MetatableName = UniqueString("metatable__" + className.GetString());
        m_ParentClassName = parentClassName;
    }

    void LuaCppClassBuilder::BindBaseMethod(UniqueString methodName, LuaCppFunction::FunctionType method, bool isStatic)
    {
        MethodBinding& binding = m_MethodBindings[methodName];

        binding.IsStatic = isStatic;
        binding.Method.Name = methodName;
        binding.Method.Function = std::make_shared<LuaCppFunction::FunctionType>(method);
    }

}
