#ifndef __ASENGINE_POOL_ALLOCATOR_H
#define __ASENGINE_POOL_ALLOCATOR_H

#include <memory>
#include <vector>
#include <cstdint>
#include <cstring>
#include <algorithm>

#include "Core/Error/Assertion.h"
#include "Core/Debug/Debug.h"


namespace ASEngine 
{

    // chunk index in the pool allocator
    using ChunkID = uint32_t;
    constexpr const ChunkID CHUNK_NULL = UINT32_MAX;

    /*
    dynanmic poolallocator implemetation
    faster than the heap, you can reserve space you want
    allocation is O(1)
    freeing is the same
    */
    template <typename T>
    class PoolAllocator
    {
    public:
    // allocator traits to interact with allocator
    private:
        using Traits = std::allocator_traits<std::allocator<T>>;

    public:
        PoolAllocator()
        {
            SetCapactity(2);
        };

        PoolAllocator(size_t capacity)
        {
            SetCapactity(capacity);
        }

        ~PoolAllocator()
        {
            // free all
            Clear();
        }

        // clear allocator
        inline void Clear()
        {
            SetCapactity(0);
        }

        // change capacity
        void SetCapactity(size_t capacity)
        {
            // allocate new space
            T* newData = nullptr;
            if (capacity > 0)
            {
                newData = m_Allocator.allocate(capacity);
                // set free flag to false
                m_IsUsed.resize(capacity);
                for (int i = static_cast<int>(m_Capacity); i < static_cast<int>(capacity); i++)
                {
                    m_IsUsed[i] = false;
                }
            }

            if (m_Data)
            {
                size_t minCapacity = (m_Capacity < capacity) ? m_Capacity: capacity;

                // copy old data to new allocated space
                if (newData)
                {
                    std::memcpy(reinterpret_cast<void *>(newData), reinterpret_cast<void *>(m_Data), minCapacity);
                }

                // free 
                for (ChunkID chunkID = capacity; chunkID < m_Capacity; chunkID++)
                {
                    if (!IsFree(chunkID))
                        Free(chunkID);
                }

                // deallocate old memory
                m_Allocator.deallocate(m_Data, m_Capacity);
            }

            // update free chunk stack
            std::vector<ChunkID> newFreeChunkStack{};
            newFreeChunkStack.reserve(capacity); 
            for (auto chunkID: m_FreeChunkStack)
            {
                if (chunkID < m_Capacity)
                    newFreeChunkStack.push_back(chunkID);
            }
            m_FreeChunkStack = std::move(newFreeChunkStack);

            // save
            m_Data = newData;
            m_Capacity = capacity;
        }

        // check if chunkid is free
        inline bool IsFree(ChunkID chunkID) const
        {
            return chunkID >= m_Capacity || !m_IsUsed[chunkID];
        };


        // allocate chunk and return the address
        inline ChunkID Allocate()
        {
            ChunkID allocatedChunkID = AllocateChunk();
            Traits::construct(m_Allocator, &m_Data[allocatedChunkID]);
            return allocatedChunkID;
        }

        // allocate push value to the allocator
        inline ChunkID Push(const T& value)
        {
            ChunkID allocatedChunkID = AllocateChunk();
            Traits::construct(m_Allocator, &m_Data[allocatedChunkID], value);
            return allocatedChunkID;
        }

        // free memory
        void Free(ChunkID chunkID)
        {
            // check if chunk is used 
            ASENGINE_ASSERT(!IsFree(chunkID), "Cannot free unused chunk!");
               
            // call destructor to logically destroy
            Traits::destroy(m_Allocator, &m_Data[chunkID]);

            // free chunk
            m_Size--;
            m_FreeChunkStack.push_back(chunkID);
        }

        // get data at 
        inline T& Get(ChunkID chunkID)
        {
            ASENGINE_ASSERT(!IsFree(chunkID), std::string(typeid(T).name()) + " : Can't get id of unused");
            return m_Data[chunkID];
        };

        // get data at
        inline const T &Get(ChunkID chunkID) const
        {
            ASENGINE_ASSERT(!IsFree(chunkID), std::string(typeid(T).name()) + " : Can't get id of unused");
            return m_Data[chunkID];
        };

        // get pool usage
        inline size_t GetSize() const
        {
            return m_Size;
        }

        // get pool capacity
        inline size_t GetCapacity() const
        {
            return m_Capacity;
        }

        // iterator
        class Iterator
        {
        public:
            Iterator(PoolAllocator<T>* poolAllocator, ChunkID chunkdID): m_PoolAllocator(poolAllocator), m_ChunkID(chunkdID) {}

            Iterator& operator++()
            {
                do {
                    m_ChunkID++;
                } 
                while (m_ChunkID < m_PoolAllocator->GetCapacity() && m_PoolAllocator->IsFree(m_ChunkID));

                return *this;
            }

            Iterator operator++(int)
            {
                Iterator itr = *this;
                ++(*this);
                return itr;
            }

            bool operator==(const Iterator& other) const
            {
                return m_PoolAllocator == other.m_PoolAllocator && m_ChunkID == other.m_ChunkID;
            }

            bool operator!=(const Iterator& other) const
            {
                return !(*this == other);
            }

            T& operator*()
            {
                return m_PoolAllocator->Get(m_ChunkID);
            }

            const T& operator*() const
            {
                return m_PoolAllocator->Get(m_ChunkID);
            }

        private:
            PoolAllocator<T>* m_PoolAllocator = nullptr;
            ChunkID m_ChunkID;
        };

        Iterator begin()
        {
            ChunkID chunkID = 0;
            while (chunkID < m_Capacity && IsFree(chunkID))
            {
                chunkID++;
            }

            return Iterator(this, chunkID);
        }

        Iterator end()
        {
            return Iterator(this, m_Capacity);
        }

    private:
        // data
        std::allocator<T> m_Allocator;
        T* m_Data = nullptr;

        size_t m_Size = 0;
        size_t m_Capacity = 0;

        // pool list of free chunks
        std::vector<ChunkID> m_FreeChunkStack{};
        std::vector<bool> m_IsUsed{};

        // allocate space   
        ChunkID AllocateChunk()
        {
            ChunkID allocatedChunkID;
            if (m_FreeChunkStack.size() > 0)
            {
                // pop free value
                allocatedChunkID = m_FreeChunkStack.back();
                m_FreeChunkStack.pop_back();
            }
            else
            {
                // grow capacity
                if (m_Size >= m_Capacity)
                {
                    SetCapactity(m_Capacity * 3 / 2 + 1);
                }
                allocatedChunkID = m_Size;
            }

            m_Size++;
            m_IsUsed[allocatedChunkID] = true;

            return allocatedChunkID;
        }
    };

} // namespace ASEngine



#endif // __ASENGINE_POOL_ALLOCATOR_H