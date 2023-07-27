#ifndef ASENGINE_POOL_ALLOCATOR_H
#define ASENGINE_POOL_ALLOCATOR_H

#include <memory>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "engine/Log/Log.h"
#include "BasePoolAllocator.h"

namespace ASEngine {

    /*
    poolallocator implemetation
    faster than the heap
    but requires to know the size of the pool
    */
    template <typename T>
    class PoolAllocator: public BasePoolAllocator {
    public:
        // types
        using Type = T;


        //contructors / deconstructors
        PoolAllocator() : BasePoolAllocator(sizeof(T)) 
        {
            InitializePoolValues();
        }

        PoolAllocator(size_t capacity) : BasePoolAllocator(sizeof(T), capacity)
        {
            InitializePoolValues();
        }

        ~PoolAllocator();


        // push value to the allocator
        ChunkID Push(const T& value);

        // free memory
        void Free(ChunkID index);

        // get at 
        inline T* Get(ChunkID index)
        {
            return m_Data + index;
        }

        // iterator
        using Iterator = class PoolAllocatorIterator
        {
        public:
            PoolAllocatorIterator(PoolAllocator<T> *pool, ChunkID currentPosition)
            {
                m_CurrentPosition = currentPosition;
                m_Pool = pool;
            };

            inline ChunkID GetCurrentPosition() const { return m_CurrentPosition; };

            inline PoolAllocatorIterator operator++(int)
            {
                m_CurrentPosition = m_Pool->Next(m_CurrentPosition);
                return *this;
            };

            inline PoolAllocatorIterator operator++()
            {
                m_CurrentPosition = m_Pool->Next(m_CurrentPosition);
                return *this;
            };

            inline T *operator*(void) const
            {
                return (T *)m_Pool->Get(m_CurrentPosition);
            };

            inline bool operator==(const PoolAllocatorIterator &it) const
            {
                return m_CurrentPosition == it.m_CurrentPosition;
            };

            inline bool operator!=(const PoolAllocatorIterator &it) const
            {
                return m_CurrentPosition != it.m_CurrentPosition;
            };

        private:
            ChunkID m_CurrentPosition = CHUNK_NULL;
            PoolAllocator<T> *m_Pool = nullptr;
        };

        // iterator begin
        inline Iterator begin()
        {
            return Iterator(this, m_Head);
        };
        // iterator end
        inline Iterator end()
        {
            return Iterator(this, UINT32_MAX);
        };

    private:
        // pool data
        T* m_Data = nullptr;

        // initialize pool data
        void InitializePoolValues();
    };


} // namespace ASEngine

#include "PoolAllocator.cpp"

#endif // ASENGINE_POOL_ALLOCATOR_H