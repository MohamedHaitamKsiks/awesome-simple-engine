#include "LuaCppClassManager.h"
#include "Core/String/UniqueStringManager.h"
#include "LuaScript/LuaScriptManager.h"

namespace ASEngine
{
    void LuaCppClassManager::Build(const LuaCppClassBuilder& builder)
    {
        auto& state = LuaScriptManager::GetInstance().GetState();

        std::vector<LuaCppFunction> staticMethods{};
        std::vector<LuaCppFunction> methods{};

        for (auto& [name, methodBinding]: builder.m_MethodBindings)
        {
            if (methodBinding.IsStatic)
                staticMethods.push_back(methodBinding.Method);
            else
                methods.push_back(methodBinding.Method);
        }

        state.CreateLibrary(builder.m_ClassName.GetString(), staticMethods);

        std::string parentMetatableName = "";
        if (builder.m_ParentClassName.GetID() != UNIQUE_STRING_ID_NULL)
            parentMetatableName = GetMetatableName(builder.m_ParentClassName).GetString();

        state.CreateMetatable(builder.m_MetatableName.GetString(), parentMetatableName, methods);
    }

    void LuaCppClassManager::RegisterLuaCppClass(std::unique_ptr<LuaCppClassBuilder> builder)
    {
        Build(*builder);
        m_MetatableNames[builder->m_ClassName] = builder->m_MetatableName;
        m_CppClassBuilders[builder->m_ClassName] = std::move(builder);
    }

    void LuaCppClassManager::Init()
    {
        /*for (const auto& [name, builder]: m_CppClassBuilders)
        {
            Build(*builder);
        }*/
    }

} // namespace ASEngine
