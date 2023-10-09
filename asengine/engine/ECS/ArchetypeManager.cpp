#include "ArchetypeManager.h"

namespace ASEngine
{
    ArchetypeManager::~ArchetypeManager()
    {
        // destroy all archetypes
        for (auto& pair: m_Archetypes)
        {
            Archetype* archetype = pair.second;
            delete archetype;
        }
    }

    Archetype* ArchetypeManager::IGetArchetype(const Signature& signature)
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
        Archetype* archetype = new Archetype();

        for (auto& name: signature)
        {
            archetype->AddComponent(name);
        }
        m_Archetypes[signature] = archetype;
    }

    bool ArchetypeManager::HasArchetype(const Signature& signature) const
    {
        return m_Archetypes.find(signature) != m_Archetypes.end();
    }

} // namespace ASEngine
