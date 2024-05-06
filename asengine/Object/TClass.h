#ifndef ASENGINE_TCLASS_H
#define ASENGINE_TCLASS_H

#include "Core/Singleton/Singleton.h"
#include "Core/String/UniqueString.h"
#include "Core/Memory/PoolAllocator.h"

#include "Class.h"
#include "Object.h"

namespace ASEngine
{
    // implementation of class 
    // each implementation is a singleton so that it is impossible to register the same class multiple time
    // objects are stored inside a pool allocator
    template <typename T>
    class TClass: public Singleton<TClass<T>>, public Class
    {
    public:
        TClass(UniqueString name): Class(name)
        {
            static_assert(std::is_base_of_v<Object, T>);
            m_Size = sizeof(T);
        }

        Object* New() override
        {
            ChunkID instanceID = m_Pool.Allocate();
            Object* instance = reinterpret_cast<Object*>(&m_Pool.Get(instanceID));
            instance->m_ID = instanceID;
            return instance;
        }

        void Destroy(Object* object) override
        {
            m_Pool.Free(object->GetID());
        }
    private:
        PoolAllocator<T> m_Pool{UINT8_MAX};
    };
} // namespace ASEngine


#endif // ASENGINE_TCLASS_H