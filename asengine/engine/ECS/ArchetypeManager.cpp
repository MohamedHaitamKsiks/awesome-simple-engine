#include "ArchetypeManager.h"

namespace ASEngine
{

    // create archetype
    bool ArchetypeManager::hasArchetype(uint32_t signature)
    {
        return archetypes.find(signature) == archetypes.end();
    }

} // namespace ASEngine
