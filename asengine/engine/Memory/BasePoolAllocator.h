#ifndef ASENGINE_BASE_POOL_ALLOCATOR_H
#define ASENGINE_BASE_POOL_ALLOCATOR_H

#include "engine/Log/Log.h"

#include <cstdint>
#include <memory>

namespace ASEngine
{
    //chunk index in the pool allocator
    using ChunkID = uint32_t;
    constexpr const ChunkID CHUNK_NULL = UINT32_MAX;

    // base class for pool allocator
    class BasePoolAllocator
    {
        public:
            // contructors
            BasePoolAllocator(size_t chunkSize);
            BasePoolAllocator(size_t chunkSize, size_t _capacity);

            // init allocator
            void Init(size_t capacity);

            // allocate chunk
            ChunkID Alloc();

            // free chunk
            void Free(ChunkID index);

            // is chunkd id used
            bool IsUsed(ChunkID index) const;

            // get capacity
            size_t GetCapacity() const;

            // get size
            size_t GetSize() const;

            // next of chunk
            ChunkID Next(ChunkID index) const;

            // previous of chunk
            ChunkID Prev(ChunkID index) const;

        protected:
            size_t m_ChunkSize = 1;
            size_t m_Size = 0;
            size_t m_Capacity = 0;

            // list of used chunks
            std::unique_ptr<bool[]> m_UsedChunks;

            // stack of all free chunks
            std::unique_ptr<ChunkID[]> m_FreeChunksStack;
            uint32_t m_FreeChunkStackPointer = 0;

            // make chunks linked list to iterate throw them
            ChunkID m_Head = CHUNK_NULL;
            ChunkID m_Foot = CHUNK_NULL;
            std::unique_ptr<ChunkID[]> m_ChunkNext;
            std::unique_ptr<ChunkID[]> m_ChunkPrev;

    };


} // namespace ASEgine


#endif