#include "ArchetypeManager.h"

namespace ASEngine
{
    Archetype& ArchetypeManager::GetArchetype(const Signature& signature)
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
        Archetype archetype{};

        for (auto& name: signature)
        {
            archetype.AddComponent(name);
        }

        m_Archetypes[signature] = std::move(archetype);
    }

    bool ArchetypeManager::HasArchetype(const Signature& signature) const
    {
        return m_Archetypes.find(signature) != m_Archetypes.end();
    }

} // namespace ASEngine
