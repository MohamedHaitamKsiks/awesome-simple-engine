#include "BasePoolAllocator.h"


namespace ASEngine
{

    BasePoolAllocator::BasePoolAllocator(size_t _chunkSize)
    {
        chunkSize = _chunkSize;
    }

    BasePoolAllocator::BasePoolAllocator(size_t _chunkSize, size_t _capacity)
    {
        chunkSize = _chunkSize;
        init(_capacity);
    }

    BasePoolAllocator::~BasePoolAllocator()
    {
        delete[] data;
    }

    void BasePoolAllocator::init(size_t _capacity)
    {
        //set capacity
        capacity = _capacity;
        
        // allocate data
        data = new uint8_t[capacity * chunkSize];

        // stack of all free chunks
        freeChunkStackPointer = capacity;
        freeChunksStack = std::make_unique<ChunkID[]>(capacity);
        
        // allocate linked list
        chunkNext = std::make_unique<ChunkID[]>(capacity);
        chunkPrev = std::make_unique<ChunkID[]>(capacity);

        // used chunks
        usedChunks = std::make_unique<bool[]>(capacity);
        for (uint32_t i = 0; i < capacity; i++)
        {
            freeChunksStack[i] = capacity - i - 1;
            usedChunks[i] = false;
            chunkNext[i] = CHUNK_NULL;
            chunkPrev[i] = CHUNK_NULL;
        }
    }

    ChunkID BasePoolAllocator::alloc()
    {
        if (getSize() == getCapacity())
            return CHUNK_NULL;

        // pop chunk id from free chunks stack
        freeChunkStackPointer--;
        ChunkID allocatedChunkId = freeChunksStack[freeChunkStackPointer];

        // use chunk
        usedChunks[allocatedChunkId] = true;

        // update linked list
        if (size != 0)
        {
            chunkNext[foot] = allocatedChunkId;
            chunkPrev[allocatedChunkId] = foot;
        }
        else
        {
            head = allocatedChunkId;
        }
        foot = allocatedChunkId;

        size++;

        return allocatedChunkId;

    }

    uint8_t* BasePoolAllocator::getRaw(ChunkID index)
    {
        return data + index * chunkSize;
    }

    void BasePoolAllocator::free(ChunkID index)
    {
        if (!isUsed(index))
            return;

        //free data
        size--;
        freeChunksStack[index];
        freeChunkStackPointer++;
        usedChunks[index] = false;
        // update linked list
        if (index == head)
        {
            head = next(index);
        }
        else if (index == foot)
        {
            chunkNext[prev(index)] = prev(index);
        }
        else
        {
            chunkNext[prev(index)] = next(index);
            chunkPrev[next(index)] = prev(index);
        }
    }

    void BasePoolAllocator::clear()
    {

    }

    bool BasePoolAllocator::isUsed(ChunkID index) const
    {
        return usedChunks[index];
    }

    size_t BasePoolAllocator::getCapacity() const
    {
        return capacity;
    }

    size_t BasePoolAllocator::getSize() const
    {
        return size;
    }

    ChunkID BasePoolAllocator::next(ChunkID index) const
    {
        return chunkNext[index];
    }

    ChunkID BasePoolAllocator::prev(ChunkID index) const
    {
        return chunkPrev[index];
    }

} // namespace ASEngine
