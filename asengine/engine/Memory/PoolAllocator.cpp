#include "PoolAllocator.h"


namespace ASEngine {

    template <typename T>
    void PoolAllocator<T>::init(size_t poolSize)
    {
        // set sizes
        maxSize = (size_t)poolSize;
        size = 0;

        // allocate space for data and
        data = new T[poolSize];
        freeChunkNext = new ChunkId[poolSize];
        usedChunks = new bool[poolSize];
        //allocate linked list space
        chunkNext = new ChunkId[poolSize];
        chunkPrev = new ChunkId[poolSize];
        // prepare freechunk linked list
        for (ChunkId i = 0; i < poolSize; i++) 
        {
            freeChunkNext[i] = (i + 1) % maxSize;
            usedChunks[i] = false;
            chunkNext[i] = i;
            chunkPrev[i] = i;
        }
    }

    template <typename T>
    PoolAllocator<T>::~PoolAllocator<T>()
    {
        delete data;
        delete freeChunkNext;
        delete usedChunks;
    }

    template <typename T>
    ChunkId PoolAllocator<T>::prev(ChunkId index)
    {
        ChunkId prevIndex = chunkPrev[index];
        if (prevIndex == index)
            return CHUNK_ID_NULL;
        return prevIndex;
    }

    template <typename T>
    ChunkId PoolAllocator<T>::next(ChunkId index)
    {
        ChunkId nextIndex = chunkNext[index];
        if (nextIndex == index)
            return CHUNK_ID_NULL;
        return nextIndex;
    }

    template <typename T>
    ChunkId PoolAllocator<T>::alloc() 
    {
        if (size == maxSize)
            return UINT32_MAX; 
        // get index
        ChunkId index = freeHead;
        usedChunks[index] = true;

        // move head to the next node
        freeHead = freeChunkNext[freeHead];

        // update linked list
        if (size != 0) {
            chunkNext[index] = head;
            chunkPrev[head] = index;
        }
        head = index;

        size++;
        return index;
    }

    template <typename T>
    void PoolAllocator<T>::free(ChunkId index) 
    {
        if (!isUsed(index))
            return;
        //call destructor of the object to simulate it's destruction
        //we need to do that since freeing objects from poolallocator doesn't destroy them from memory
        //but since it's logically free we can call the destructor and simulate to make it equivilent to delete operator
        get(index)->~T();
        //free data
        size--;
        freeChunkNext[index] = freeHead;
        freeHead = index;
        usedChunks[index] = false;
        //update linked list
        if (index == head) 
        {
            head = next(index);
        }
        else if (next(index) == UINT32_MAX)
        {
            chunkNext[prev(index)] = prev(index);
        }
        else
        {
            chunkNext[prev(index)] = next(index);
            chunkPrev(next(index)) = prev(index);
        }
    }

    template <typename T>
    bool PoolAllocator<T>::isUsed(ChunkId index)
    {
        return usedChunks[index];
    }

    template <typename T>
    T *PoolAllocator<T>::get(ChunkId index)
    {
        if (!isUsed(index))
            return nullptr;
        return data + index;
    }

    template <typename T>
    size_t PoolAllocator<T>::getMaxSize()
    {
        return maxSize;
    }

    template <typename T>
    size_t PoolAllocator<T>::getSize()
    {
        return size;
    }

} // namespace ASEngine
