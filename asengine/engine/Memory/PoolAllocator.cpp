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
        // prepare freechunk linked list
        for (ChunkId i = 0; i < poolSize; i++) 
        {
            freeChunkNext[i] = (i + 1) % maxSize;
            usedChunks[i] = false;
        }
    }

    template <typename T>
    void PoolAllocator<T>::terminate()
    {
        delete data;
        delete freeChunkNext;
        delete usedChunks;
    }



    template <typename T>
    ChunkId PoolAllocator<T>::alloc() 
    {
        // get index
        ChunkId index = freeHead;
        usedChunks[index] = true;

        // move head to the next node
        freeHead = freeChunkNext[freeHead];
        // increase size
        size++;
        return index;
    }

    template <typename T>
    void PoolAllocator<T>::free(ChunkId index) 
    {
        if (!isUsed(index))
            return;
        freeChunkNext[index] = freeHead;
        freeHead = index;
        usedChunks[index] = false;
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
