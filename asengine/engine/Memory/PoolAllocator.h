#ifndef ASENGINE_POOL_ALLOCATOR_H
#define ASENGINE_POOL_ALLOCATOR_H

#include <cstddef>
#include <cstdint>
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
        PoolAllocator<T>() : BasePoolAllocator(sizeof(T)) {};

        PoolAllocator<T>(size_t _capacity) : BasePoolAllocator(sizeof(T), _capacity){}

        // free 
        void free(ChunkID index);

        // get at 
        T* get(ChunkID index);

        // iterator
        using Iterator = PoolAllocatorIterator<T>;

        // begin
        Iterator begin()
        {
            return Iterator(this, head);
        };
        // end
        Iterator end()
        {
            return Iterator(this, UINT32_MAX);
        };

    };

} // namespace ASEngine

#include "PoolAllocator.cpp"

#endif // ASENGINE_POOL_ALLOCATOR_H