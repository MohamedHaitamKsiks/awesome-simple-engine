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
        // is resource owner
        inline bool IsOwner() const
        {
            return m_Owner;
        }

    private:
        bool m_Owner = true;
        
    };

} // namespace ASEngine


#endif