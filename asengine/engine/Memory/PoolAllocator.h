#ifndef ASENGINE_POOL_ALLOCATOR_H
#define ASENGINE_POOL_ALLOCATOR_H

#include <memory>
#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "engine/Log/Log.h"
#include "DynamicArray.h"

namespace ASEngine {

    // chunk index in the pool allocator
    using ChunkID = uint32_t;
    constexpr const ChunkID CHUNK_NULL = UINT32_MAX;

    // base class of pool allocator
    class PoolAllocator
    {
    public:
        PoolAllocator(size_t capacity); 

        // allocate chunk in pool allcoator
        ChunkID Alloc();

        // free chunk 
        void Free(ChunkID chunkID);

        // get pool usage
        inline size_t GetSize()  const 
        {
            return m_Size;
        };


    private:
        size_t m_Size = 0;

        // pool list of free chunks
        TDynamicArray<ChunkID> m_FreeChunkStack{};
    };

    /*
    dynanmic poolallocator implemetation
    faster than the heap, you can reserve space you want
    */
    template <typename T>
    class TPoolAllocator : public PoolAllocator
    {
    public:

        // chunk
        using Chunk = struct PoolAllocatorChunk
        {
            T Data;
            bool Used = false;
        };

        TPoolAllocator(size_t capacity) : PoolAllocator(capacity)
        {
            m_Data.Reserve(capacity);
        }

        ~TPoolAllocator()
        {
        }

        // allocate chunk and return the address
        ChunkID Alloc()
        {
            ChunkID allocatedChunkID = PoolAllocator::Alloc();
            if (allocatedChunkID == GetSize() - 1)
            {
                m_Data.Add();
            }
            m_Data[allocatedChunkID].Used = true;
            return allocatedChunkID;
        }

        // push value to the allocator
        ChunkID Push(const T& value)
        {
            ChunkID allocatedChunkID = Alloc();
            m_Data[allocatedChunkID].Data = value;
            return allocatedChunkID;
        }

        // free memory
        void Free(ChunkID chunkID)
        {
            if (!m_Data[chunkID].Used)
            {
                Debug::Log(chunkID, ": This Chunk has already been freed.");
                return;
            }

             // call destructor to logically destroy
             m_Data[chunkID].Data.~T();

             // free chunk
             PoolAllocator::Free(chunkID);
        }

        // get data at 
        inline T& Get(ChunkID chunkID)
        {
            return m_Data[chunkID].Data;
        };

    private:
        // pool data
        TDynamicArray<Chunk> m_Data{};
    };

} // namespace ASEngine



#endif // ASENGINE_POOL_ALLOCATOR_H