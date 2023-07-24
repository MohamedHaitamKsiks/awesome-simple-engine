#ifndef ASENGINE_STACK_ALLOCATOR_H
#define ASENGINE_STACK_ALLOCATOR_H

#include "BaseStackAllocator.h"

namespace ASEngine
{
    template <typename T>
    class StackAllocator: public BaseStackAllocator
    {
    public:
        StackAllocator(size_t size): BaseStackAllocator(size * sizeof(T)) {};

        // push data
        inline bool Push(const T &data)
        {
            return PushRaw((uint8_t*) &data, sizeof(T));
        };

        // pop data
        inline T* Pop()
        {
            return (T*) PopRaw(sizeof(T));
        };

        inline T* GetData()
        {
            return (T*) m_Data;
        };

        inline size_t GetObjectCount()
        {
            return GetSize() / sizeof(T);
        };
    };
    
} // namespace ASEngine


#endif // ASENGINE_STACK_ALLOCATOR_H