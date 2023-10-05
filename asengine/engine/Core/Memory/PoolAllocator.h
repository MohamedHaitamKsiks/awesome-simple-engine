#ifndef ASENGINE_POOL_ALLOCATOR_H
#define ASENGINE_POOL_ALLOCATOR_H

#include <memory>

#include <cstdlib>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cassert>

#include "DynamicArray.h"
#include "Core/Log/Log.h"

namespace ASEngine {

    // chunk index in the pool allocator
    using ChunkID = uint32_t;
    constexpr const ChunkID CHUNK_NULL = UINT32_MAX;

    // base class of pool allocator
    class PoolAllocator
    {
    public:

        // allocate chunk in pool allcoator
        virtual ChunkID Alloc() = 0;

        // free chunk 
        virtual void Free(ChunkID chunkID) = 0;

        // get pool usage
        inline size_t GetSize()  const 
        {
            return m_Size;
        };

        // get pool capacityt
        inline size_t GetCapacity() const
        {
            return m_Capacity;
        };

    protected:
        size_t m_Size = 0;
        size_t m_Capacity = 0;

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

        TPoolAllocator() {};

        TPoolAllocator(size_t capacity)
        {
            m_Capacity = capacity;
            
            for (size_t i = 0; i < capacity; i++)
            {
                m_FreeChunkStack.Push((ChunkID)capacity - 1 - i);

                m_Data.Add();
                m_Data[i].Used = false;
            }
        }

        ~TPoolAllocator()
        {
        }

        // check if chunkid is free
        inline bool IsFree(ChunkID chunkID)
        {
            return chunkID >= GetCapacity() || !m_Data[chunkID].Used;
        };


        // allocate chunk and return the address
        ChunkID Alloc()
        {
            ChunkID allocatedChunkID;
            if (m_FreeChunkStack.GetSize() > 0)
            {
                // pop free value
                allocatedChunkID = m_FreeChunkStack.Pop();
            }
            else
            {
                m_Data.Add();
                allocatedChunkID = m_Capacity;
                m_Capacity++;
            }
            
            m_Size++;
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
            assert(m_Data[chunkID].Used);
            // call destructor to logically destroy
            m_Data[chunkID].Data.~T();
            m_Data[chunkID].Used = false;

            // free chunk
            m_Size--;
            m_FreeChunkStack.Push(chunkID);
        }

        // get data at 
        inline T& Get(ChunkID chunkID)
        {
            return m_Data[chunkID].Data;
        };

        // get data at
        inline const T &Get(ChunkID chunkID) const
        {
            return m_Data[chunkID].Data;
        };

    private:
        // pool data
        TDynamicArray<Chunk> m_Data{};
    };

} // namespace ASEngine



#endif // ASENGINE_POOL_ALLOCATOR_H