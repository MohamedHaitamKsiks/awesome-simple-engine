#ifndef ASENGINE_ENTITY_DATA_H
#define ASENGINE_ENTITY_DATA_H

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
    };



} // namespace ASEngine


#endif