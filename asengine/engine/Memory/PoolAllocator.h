#ifndef ASENGINE_POOL_ALLOCATOR_H
#define ASENGINE_POOL_ALLOCATOR_H

#include <cstddef>
#include <cstdint>


namespace ASEngine {

    //poolallocator implemetation
    //faster than the heap
    //will be used in

    typedef uint32_t ChunkId;

    template <typename T>
    class PoolAllocator {
    public:
        // init pool allocator
        void init(size_t poolSize);
        void terminate();

        // returns the index of the allocated ressource
        ChunkId alloc();

        // free index
        void free(ChunkId index);

        // is chunk used
        bool isUsed(ChunkId index);

        // get data at position
        T* get(ChunkId index);

        // get maximum allocation size
        size_t getMaxSize();

        // get allocator size
        size_t getSize();

    private:
        T* data = nullptr;
        size_t maxSize = 0;
        size_t size = 0;
        
        // linked list of all free chunks
        ChunkId freeHead = 0;
        ChunkId *freeChunkNext = nullptr;
        bool *usedChunks = nullptr;
    };

} // namespace ASEngine

#endif // ASENGINE_POOL_ALLOCATOR_H