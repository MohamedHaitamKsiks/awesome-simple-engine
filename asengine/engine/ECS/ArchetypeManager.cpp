#include "ArchetypeManager.h"

namespace ASEngine
{

    // create archetype
    bool ArchetypeManager::HasArchetype(uint32_t signature) const
    {
        return m_Archetypes.find(signature) != m_Archetypes.end();
    }

} // namespace ASEngine
