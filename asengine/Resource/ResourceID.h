#ifndef __ASENGINE_RESOURCE_ID_H
#define __ASENGINE_RESOURCE_ID_H

#include "Core/Memory/PoolAllocator.h"

namespace ASEngine
{
    using ResourceID = ChunkID;
    constexpr const ResourceID RESOURCE_ID_NULL = CHUNK_NULL;
} // namespace ASEngine


#endif // __ASENGINE_RESOURCE_ID_H