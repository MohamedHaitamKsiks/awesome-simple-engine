#ifndef ASENGINE_POOL_ALLOCATOR_H
#define ASENGINE_POOL_ALLOCATOR_H

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "engine/Log/Log.h"
#include "BasePoolAllocator.h"

namespace ASEngine {

    /*
    poolallocator implemetation
    faster than the heap
    but requires to know the size of the pool
    */
    template <typename T>
    class PoolAllocator: public BasePoolAllocator {
    public:
        // types
        using Type = T;


        //contructors / deconstructors
        PoolAllocator() : BasePoolAllocator(sizeof(T)) 
        {
            InitializePoolValues();
        };

        PoolAllocator(size_t capacity) : BasePoolAllocator(sizeof(T), capacity)
        {
            InitializePoolValues();
        };

        // push value to the allocator
        ChunkID Push(const T& value);

        // free memory
        void Free(ChunkID index);

        // get at 
        T* Get(ChunkID index);

        // iterator
        using Iterator = PoolAllocatorIterator<T>;

        // iterator begin
        inline Iterator begin()
        {
            return Iterator(this, m_Head);
        };
        // iterator end
        inline Iterator end()
        {
            return Iterator(this, UINT32_MAX);
        };

    private:
        void InitializePoolValues();

    };

} // namespace ASEngine

#include "PoolAllocator.cpp"

#endif // ASENGINE_POOL_ALLOCATOR_H