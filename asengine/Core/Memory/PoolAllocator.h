#ifndef __ASENGINE_POOL_ALLOCATOR_H
#define __ASENGINE_POOL_ALLOCATOR_H

#include <memory>
#include <vector>
#include <cstdint>
#include <cstring>
#include <algorithm>

#include "ChunkID.h"
#include "PoolAllocatorPage.h"

#include "Core/Error/Assertion.h"
#include "Core/Debug/Debug.h"
#include "API/API.h"

namespace ASEngine 
{
    constexpr const size_t POOL_ALLOCATOR_DEFAULT_PAGE_SIZE = UINT16_MAX;

    /*
    dynanmic poolallocator implemetation
    faster than the heap, you can reserve space you want
    allocation is O(1)
    freeing is the same
    */
    template <typename T>
    class ASENGINE_API PoolAllocator
    {
    public:
    // allocator traits to interact with allocator
    public:
        PoolAllocator()
        {
            PushPage();
        };

        PoolAllocator(size_t pageCount)
        {
            for (size_t i = 0; i < pageCount; i++)
                PushPage();
        }

        PoolAllocator(const PoolAllocator&) = delete;
        PoolAllocator(PoolAllocator&&) = delete;

        ~PoolAllocator()
        {
            Clear();
        }

        // clear allocator
        inline void Clear()
        {
            while (m_Pages.size() > 0)
                m_Pages.pop_back();

            m_FreeChunkStack.clear();
        }

        // check if chunkid is free
        inline bool IsFree(ChunkID chunkID) const
        {
            return m_Pages.size() == 0 ||
                chunkID >= GetCapacity() || 
                !m_Pages[chunkID / m_PageSize]->IsUsed(chunkID % m_PageSize);
        }

        // free memory
        inline void Free(ChunkID chunkID)
        {
            ASENGINE_ASSERT(!IsFree(chunkID), "Can't free unused");
            m_Pages[chunkID / m_PageSize]->Destroy(chunkID % m_PageSize);
            
            m_FreeChunkStack.push_back(chunkID);
            m_Size--;
        }

        // allocate memory
        inline ChunkID Allocate()
        {
            ChunkID allocatedChunkID = AllocateChunk();
            m_Pages[allocatedChunkID / m_PageSize]->Construct(allocatedChunkID % m_PageSize);

            return allocatedChunkID;
        }

        // get data at
        inline T& Get(ChunkID chunkID)
        {
            ASENGINE_ASSERT(!IsFree(chunkID), "Can't get id of unused");
            return m_Pages[chunkID / m_PageSize]->Get(chunkID % m_PageSize);
        };

        // get data at
        inline const T &Get(ChunkID chunkID) const
        {
            ASENGINE_ASSERT(!IsFree(chunkID), "Can't get id of unused");
            return m_Pages[chunkID / m_PageSize]->Get(chunkID % m_PageSize);
        };

        // get pool usage
        inline size_t GetSize() const
        {
            return m_Size;
        }

        // get pool capacity
        inline size_t GetCapacity() const
        {
            return m_Pages.size() * m_PageSize;
        }

        // get page size
        inline size_t GetPageSize() const
        {
            return m_PageSize;
        }

    private:
        // page type
        using Page = PoolAllocatorPage<T>;

        // data
        std::vector<std::unique_ptr<Page>> m_Pages{};
        size_t m_PageSize = POOL_ALLOCATOR_DEFAULT_PAGE_SIZE;
        size_t m_Size = 0;

        // pool list of free chunks
        std::vector<ChunkID> m_FreeChunkStack{};

        // allocate one chunk and return it's id (doesn't construct) 
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
                if (m_Size >= GetCapacity())
                {
                    PushPage();
                }
                allocatedChunkID = m_Size;
            }

            m_Size++;
            return allocatedChunkID;
        }

        // add new page of chunks
        void PushPage()
        {
            // allocate and add page data
            std::unique_ptr<Page> page = std::make_unique<Page>(m_PageSize);
            m_Pages.push_back(std::move(page));
        }

        // pop page of chunks
        void PopPage()
        {
            // remove page
            m_Pages.pop_back();

            // recompute free chunks stack
            size_t capacity = GetCapacity();

            std::vector<ChunkID> newFreeChunkStack{};
            newFreeChunkStack.reserve(capacity);

            for (auto chunkID : m_FreeChunkStack)
            {
                if (chunkID < capacity)
                    newFreeChunkStack.push_back(chunkID);
            }
            m_FreeChunkStack = std::move(newFreeChunkStack);


        }
    };

} // namespace ASEngine



#endif // __ASENGINE_POOL_ALLOCATOR_H