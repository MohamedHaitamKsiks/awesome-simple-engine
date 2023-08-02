#include "PoolAllocator.h"


namespace ASEngine 
{
    PoolAllocator::PoolAllocator(size_t capacity)
    {
        m_FreeChunkStack.Reserve(capacity);
    }

    ChunkID PoolAllocator::Alloc()
    {
        // allocate chunk
        ChunkID allocatedChunkID;
        if (m_FreeChunkStack.GetSize() > 0)
        {
            // pop free value
            allocatedChunkID = m_FreeChunkStack.Pop();
        }
        else
        {
            allocatedChunkID = m_Size;
        }
        m_Size++;

        return allocatedChunkID;
    }

    void PoolAllocator::Free(ChunkID chunkID)
    {
        m_Size--;
        m_FreeChunkStack.Push(chunkID);
    }

} // namespace ASEngine
