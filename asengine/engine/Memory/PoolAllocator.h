#ifndef ASENGINE_POOL_ALLOCATOR_H
#define ASENGINE_POOL_ALLOCATOR_H

#include <cstddef>
#include <cstdint>

#define CHUNK_ID_NULL UINT32_MAX;

namespace ASEngine {

    typedef uint32_t ChunkId;

    /*
    poolallocator implemetation
    faster than the heap
    but requires to know the size of the pool
    */
    template <typename T>
    class PoolAllocator {
    public:
        // init pool allocator
        void init(size_t poolSize);
        ~PoolAllocator<T>();

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

        // make chunks as linked list to iterate with them
        ChunkId head = 0;
        ChunkId* chunkNext = nullptr;
        ChunkId* chunkPrev = nullptr;

        // next of chunk
        ChunkId next(ChunkId index);
        // previous of chunk
        ChunkId prev(ChunkId index);

    };

} // namespace ASEngine

#include "PoolAllocator.cpp"

#endif // ASENGINE_POOL_ALLOCATOR_H