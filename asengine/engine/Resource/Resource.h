#ifndef ASENGINE_RESOURCE_H
#define ASENGINE_RESOURCE_H

#include "../Memory/PoolAllocator.h"

namespace ASEngine
{
    // 32 bits integer used to reference resources
    using ResourceID = ChunkID;

    // abstract class for resources
    // parent of all resources
    class Resource 
    {
    public:
        // resource id
        ResourceID ID;


    private:

        
    };

} // namespace ASEngine


#endif