#ifndef ASENGINE_RESOURCE_ID
#define ASENGINE_RESOURCE_ID

#include "Core/Memory/PoolAllocator.h"

namespace ASEngine
{
    using ResourceID = ChunkID;
    constexpr const ResourceID RESOURCE_ID_NULL = CHUNK_NULL;
} // namespace ASEngine


#endif // ASENGINE_RESOURCE_ID