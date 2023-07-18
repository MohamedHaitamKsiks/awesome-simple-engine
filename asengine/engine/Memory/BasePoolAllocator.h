#ifndef ASENGINE_BASE_POOL_ALLOCATOR_H
#define ASENGINE_BASE_POOL_ALLOCATOR_H

#include <cstdint>
#include <memory>

namespace ASEngine
{
    //chunk index in the poEol allocator
    using ChunkID = uint32_t;
    constexpr const ChunkID CHUNK_NULL = UINT32_MAX;

    // base class for pool allocator
    class BasePoolAllocator
    {
        public:
            // contructors
            BasePoolAllocator(size_t chunkSize);
            BasePoolAllocator(size_t chunkSize, size_t _capacity);

            ~BasePoolAllocator();

            // init allocator
            void Init(size_t capacity);

            // allocate chunk
            ChunkID Alloc();

            // get at index
            uint8_t* GetRaw(ChunkID index); 

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
            // data
            uint8_t* m_Data = nullptr;

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

    // pool allocator iterator
    template <typename T>
    class PoolAllocatorIterator
    {
    public:
        PoolAllocatorIterator(BasePoolAllocator* pool, ChunkID currentPosition)
        {
            m_CurrentPosition = currentPosition;
            m_Pool = pool;
        };

        inline ChunkID GetCurrentPosition() const { return m_CurrentPosition; };

        inline PoolAllocatorIterator<T> operator++(int)
        {
            m_CurrentPosition = m_Pool->Next(m_CurrentPosition);
            return *this;
        };

        inline PoolAllocatorIterator<T> operator++()
        {
            m_CurrentPosition = m_Pool->Next(m_CurrentPosition);
            return *this;
        };

        inline T* operator*(void) const
        {
            return (T *) m_Pool->GetRaw(m_CurrentPosition);
        };

        inline bool operator==(const PoolAllocatorIterator<T> &it) const
        {
            return m_CurrentPosition == it.m_CurrentPosition;
        };

        inline bool operator!=(const PoolAllocatorIterator<T> &it) const
        {
            return m_CurrentPosition != it.m_CurrentPosition;
        };
    private:
        ChunkID m_CurrentPosition = CHUNK_NULL;
        BasePoolAllocator *m_Pool = nullptr;
    };

} // namespace ASEgine


#endif