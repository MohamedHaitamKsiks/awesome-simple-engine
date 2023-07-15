#ifndef ASENGINE_BASE_POOL_ALLOCATOR_H
#define ASENGINE_BASE_POOL_ALLOCATOR_H

#include <cstdint>
#include <memory>

namespace ASEngine
{
    //chunk index in the poEol allocator
    using ChunkID = uint32_t;
    const ChunkID CHUNK_NULL = UINT32_MAX;

    // base class for pool allocator
    class BasePoolAllocator
    {
        public:
            // contructors
            BasePoolAllocator(size_t _chunkSize);
            BasePoolAllocator(size_t _chunkSize, size_t _capacity);

            ~BasePoolAllocator();

            // init allocator
            void init(size_t _capacity);

            // allocate chunk
            ChunkID alloc();

            // get at index
            uint8_t* getRaw(ChunkID index); 

            // free chunk
            void free(ChunkID index);

            // clear allocator
            void clear();

            // is chunkd id used
            bool isUsed(ChunkID index) const;

            // get capacity
            size_t getCapacity() const;

            // get size
            size_t getSize() const;

            // next of chunk
            ChunkID next(ChunkID index) const;

            // previous of chunk
            ChunkID prev(ChunkID index) const;

        protected:
            // data
            uint8_t* data = nullptr;

            size_t chunkSize = 1;
            size_t size = 0;
            size_t capacity = 0;

            // list of used chunks
            std::unique_ptr<bool[]> usedChunks;

            // stack of all free chunks
            std::unique_ptr<ChunkID[]> freeChunksStack;
            uint32_t freeChunkStackPointer = 0;

            // make chunks linked list to iterate throw them
            ChunkID head = CHUNK_NULL;
            ChunkID foot = CHUNK_NULL;
            std::unique_ptr<ChunkID[]> chunkNext;
            std::unique_ptr<ChunkID[]> chunkPrev;
            
    };

    // pool allocator iterator
    template <typename T>
    struct PoolAllocatorIterator
    {
        ChunkID currentPosition = CHUNK_NULL;
        BasePoolAllocator* out;

        PoolAllocatorIterator(BasePoolAllocator* _out, ChunkID _currentPosition)
        {
            currentPosition = _currentPosition;
            out = _out;
        };

        PoolAllocatorIterator<T> operator++(int)
        {
            currentPosition = out->next(currentPosition);
            return *this;
        };

        PoolAllocatorIterator<T> operator++()
        {
            currentPosition = out->next(currentPosition);
            return *this;
        };

        T* operator*(void) const
        {
            return (T*) out->getRaw(currentPosition);
        };

        bool operator==(const PoolAllocatorIterator<T> &it) const
        {
            return currentPosition == it.currentPosition;
        };

        bool operator!=(const PoolAllocatorIterator<T> &it) const
        {
            return currentPosition != it.currentPosition;
        };
    };

} // namespace ASEgine


#endif