#ifndef __ASENGINE_POOL_ALLOCATOR_PAGE_H
#define __ASENGINE_POOL_ALLOCATOR_PAGE_H

#include <memory>
#include "MallocAllocator.h"
#include "ChunkID.h"


namespace ASEngine
{
    template<typename T>
    class PoolAllocatorPage
    {
    public:
        // pool allocator page 
        PoolAllocatorPage(size_t size)
        {
            // create data space
            m_Data = m_Allocator.allocate(size);

            // create is used array
            m_IsUsed = std::make_unique<bool[]>(size);
            for (size_t i = 0; i < size; i++)
                m_IsUsed[i] = false;

            m_Size = size;
        }

        ~PoolAllocatorPage()
        {
            // destroy remaning chunks
            for (ChunkID localChunkID = 0; localChunkID < static_cast<ChunkID>(m_Size); localChunkID++)
            {
                if (IsUsed(localChunkID))
                    Destroy(localChunkID);
            }

            // free data
            m_Allocator.deallocate(m_Data, m_Size);
            m_Data = nullptr;
            m_Size = 0;
        }

        // get chunk at 
        inline T& Get(ChunkID localChunkID)
        {
            return m_Data[localChunkID];
        }

        // get chunk at
        inline const T& Get(ChunkID localChunkID) const
        {
            return m_Data[localChunkID];
        }

        // get chunk used state
        inline bool IsUsed(ChunkID localChunkID) const
        {
            return m_IsUsed[localChunkID];
        }

        // get size
        inline size_t GetSize() const
        {
            return m_Size;
        }

        // allocate chunk
        inline void Construct(ChunkID localChunkID)
        {
            std::construct_at(&m_Data[localChunkID]);
            m_IsUsed[localChunkID] = true;
        }

        // destroy chunk
        inline void Destroy(ChunkID localChunkID)
        {
            std::destroy_at(&m_Data[localChunkID]);
            m_IsUsed[localChunkID] = false;
        }

    private:
        T* m_Data = nullptr;
        MallocAllocator<T> m_Allocator;

        std::unique_ptr<bool[]> m_IsUsed;
        
        size_t m_Size = 0;
    };
} // namespace ASEngine


#endif // __ASENGINE_POOL_ALLOCATOR_PAGE_H
