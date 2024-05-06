#ifndef ASENGINE_IOBJECT_H
#define ASENGINE_IOBJECT_H

#include "Core/Memory/PoolAllocator.h"
#include "Core/String/UniqueString.h"

namespace ASEngine
{
    using ObjectID = ChunkID;

    // template of generic object 
    class Object
    {
    public:
        Object() = default;
        virtual UniqueString GetClassName() const = 0;
        
        inline ObjectID GetID() const
        {
            return m_ID;
        } 
    private:
        ObjectID m_ID;
        template<typename T>
        friend class TClass;
    };
} // namespace ASEngine


#endif // ASENGINE_IOBJECT_H