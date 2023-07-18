#include "BasePoolAllocator.h"


namespace ASEngine
{

    BasePoolAllocator::BasePoolAllocator(size_t chunkSize)
    {
        m_ChunkSize = chunkSize;
    }

    BasePoolAllocator::BasePoolAllocator(size_t chunkSize, size_t capacity)
    {
        m_ChunkSize = chunkSize;
        Init(capacity);
    }

    BasePoolAllocator::~BasePoolAllocator()
    {
        delete[] m_Data;
    }

    void BasePoolAllocator::Init(size_t capacity)
    {
        //set capacity
        m_Capacity = capacity;
        
        // allocate data
        m_Data = new uint8_t[m_Capacity * m_ChunkSize];

        // stack of all free chunks
        m_FreeChunkStackPointer = m_Capacity;
        m_FreeChunksStack = std::make_unique<ChunkID[]>(m_Capacity);
        
        // allocate linked list
        m_ChunkNext = std::make_unique<ChunkID[]>(m_Capacity);
        m_ChunkPrev = std::make_unique<ChunkID[]>(m_Capacity);

        // used chunks
        m_UsedChunks = std::make_unique<bool[]>(m_Capacity);

        for (uint32_t i = 0; i < m_Capacity; i++)
        {
            m_FreeChunksStack[i] = m_Capacity - i - 1;
            m_UsedChunks[i] = false;
            m_ChunkNext[i] = CHUNK_NULL;
            m_ChunkPrev[i] = CHUNK_NULL;
        }
    }

    ChunkID BasePoolAllocator::Alloc()
    {
        if (GetSize() == GetCapacity())
            return CHUNK_NULL;

        // pop chunk id from free chunks stack
        m_FreeChunkStackPointer--;
        ChunkID allocatedChunkId = m_FreeChunksStack[m_FreeChunkStackPointer];

        // use chunk
        m_UsedChunks[allocatedChunkId] = true;

        // update linked list
        if (m_Size != 0)
        {
            m_ChunkNext[m_Foot] = allocatedChunkId;
            m_ChunkPrev[allocatedChunkId] = m_Foot;
        }
        else
        {
            m_Head = allocatedChunkId;
        }
        m_Foot = allocatedChunkId;

        m_Size++;

        return allocatedChunkId;

    }

    uint8_t* BasePoolAllocator::GetRaw(ChunkID index)
    {
        return m_Data + index * m_ChunkSize;
    }

    void BasePoolAllocator::Free(ChunkID index)
    {
        if (!IsUsed(index))
            return;

        //free data
        m_Size--;
        m_FreeChunksStack[index];
        m_FreeChunkStackPointer++;
        m_UsedChunks[index] = false;

        // update linked list
        if (index == m_Head)
        {
            m_Head = Next(index);
        }
        else if (index == m_Foot)
        {
            m_Foot = Prev(index);
            m_ChunkNext[m_Foot] = CHUNK_NULL;
        }
        else
        {
            m_ChunkNext[Prev(index)] = Next(index);
            m_ChunkPrev[Next(index)] = Prev(index);
        }
    }

    bool BasePoolAllocator::IsUsed(ChunkID index) const
    {
        return m_UsedChunks[index];
    }

    size_t BasePoolAllocator::GetCapacity() const
    {
        return m_Capacity;
    }

    size_t BasePoolAllocator::GetSize() const
    {
        return m_Size;
    }

    ChunkID BasePoolAllocator::Next(ChunkID index) const
    {
        return m_ChunkNext[index];
    }

    ChunkID BasePoolAllocator::Prev(ChunkID index) const
    {
        return m_ChunkPrev[index];
    }

} // namespace ASEngine
