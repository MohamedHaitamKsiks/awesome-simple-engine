#include "ArchetypeManager.h"

namespace ASEngine
{

    // create archetype
    bool ArchetypeManager::hasArchetype(uint32_t signature) const
    {
        return archetypes.find(signature) != archetypes.end();
    }

} // namespace ASEngine
