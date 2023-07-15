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
            initializePoolValues();
        };

        PoolAllocator(size_t _capacity) : BasePoolAllocator(sizeof(T), _capacity)
        {
            initializePoolValues();
        };

        // free memory
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

    private:
        void initializePoolValues();

    };

} // namespace ASEngine

#include "PoolAllocator.cpp"

#endif // ASENGINE_POOL_ALLOCATOR_H