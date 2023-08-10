#include "ArchetypeManager.h"

namespace ASEngine
{

    std::shared_ptr<Archetype> ArchetypeManager::IGetArchetype(TDynamicArray<UniqueString> &componentNames)
    {
        uint32_t signature = ComponentManager::GetSignature(componentNames);
        // is archetype doesn't exist create it
        if (!HasArchetype(signature))
        {
            CreateArchetype(componentNames);
        }
        return m_Archetypes[signature];
    }

    void ArchetypeManager::CreateArchetype(TDynamicArray<UniqueString> &componentNames)
    {
        uint32_t signature = ComponentManager::GetSignature(componentNames);
        std::shared_ptr<Archetype> archetype = std::make_shared<Archetype>();

        for (auto& name: componentNames)
        {
            archetype->AddComponent(name);
        }
        m_Archetypes[signature] = archetype;

        SystemManager::RegisterArchetype(archetype);
    }

    bool ArchetypeManager::HasArchetype(uint32_t signature) const
    {
        return m_Archetypes.find(signature) != m_Archetypes.end();
    }

} // namespace ASEngine
