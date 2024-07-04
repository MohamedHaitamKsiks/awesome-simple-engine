#ifndef __ASENGINE_ENTITY_DATA_H
#define __ASENGINE_ENTITY_DATA_H

#include <memory>
#include <vector>

#include "Component.h"
#include "Archetype.h"

#include "API/API.h"

namespace ASEngine
{
    // entity data for look up ..
    struct ASENGINE_API EntityData
    {
        Archetype* ArchetypeOwner = nullptr;
        bool IsDestroyed = false;
        bool Persistent = false;
    };

} // namespace ASEngine


#endif