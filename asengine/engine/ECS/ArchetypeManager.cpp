#include "ArchetypeManager.h"

namespace ASEngine
{

    std::shared_ptr<Archetype> ArchetypeManager::IGetArchetype(const Signature& signature)
    {
        // is archetype doesn't exist create it
        if (!HasArchetype(signature))
        {
            CreateArchetype(signature);
        }
        return m_Archetypes[signature];
    }

    void ArchetypeManager::CreateArchetype(const Signature& signature)
    {
        std::shared_ptr<Archetype> archetype = std::make_shared<Archetype>();

        for (auto& name: signature)
        {
            archetype->AddComponent(name);
        }
        m_Archetypes[signature] = archetype;

        SystemManager::RegisterArchetype(archetype);
    }

    bool ArchetypeManager::HasArchetype(const Signature& signature) const
    {
        return m_Archetypes.find(signature) != m_Archetypes.end();
    }

} // namespace ASEngine
