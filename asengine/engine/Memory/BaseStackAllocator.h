#ifndef ASENGINE_BASE_STACK_ALLOCATOR_H
#define ASENGINE_BASE_STACK_ALLOCATOR_H

#include <cstring>
#include <memory>
#include <cstdint>

namespace ASEngine
{
    class BaseStackAllocator
    {
    public:
        BaseStackAllocator(size_t size);
        ~BaseStackAllocator();

        // get size
        inline size_t GetSize()
        {
            return m_StackPointer;
        };

        // get capacity
        inline size_t GetCapacity()
        {
            return m_StackCapacity;
        };

        // delete all data from allocator
        inline void Clear()
        {
            m_StackPointer = 0;
        };

    protected :
        uint8_t *m_Data = nullptr;
        size_t m_StackPointer = 0;
        size_t m_StackCapacity = 0;

        // push raw data 
        bool PushRaw(const uint8_t *data, size_t size);
        // pop data
        uint8_t *PopRaw(size_t size);
    };    
} // namespace ASEngine

#endif // ASENGINE_BASE_STACK_ALLOCATOR_H