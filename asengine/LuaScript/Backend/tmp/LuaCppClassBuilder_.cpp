/*#include "LuaCppClassBuilder.h"
#include "Core/String/UniqueString.h"

namespace ASEngine
{
    LuaCppClassBuilder::LuaCppClassBuilder(const std::string& className)
    {
        m_ClassName = className;
    }

    void LuaCppClassBuilder::BindMethod(const std::string& methodName, int (*method)(void*), bool isStatic)
    {
        MethodBinding& binding = m_MethodBindings[methodName];
        binding.IsStatic = isStatic;
        binding.Method.Name = UniqueString(methodName);
        binding.Method.Function = method;
    }
}
*/
