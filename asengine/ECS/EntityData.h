#ifndef __ASENGINE_ENTITY_DATA_H
#define __ASENGINE_ENTITY_DATA_H

#include <memory>
#include <vector>

#include "Component.h"
#include "Archetype.h"

namespace ASEngine
{
    // entity data for look up ..
    struct EntityData
    {
        Archetype* ArchetypeOwner = nullptr;
        bool IsDestroyed = false;
        bool Persistent = false;
    };

} // namespace ASEngine


#endif