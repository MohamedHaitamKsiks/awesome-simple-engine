#ifndef ASENGINE_BASE_POOL_ALLOCATOR_H
#define ASENGINE_BASE_POOL_ALLOCATOR_H

#include <memory>
#include <cstdint>

namespace ASEgine
{
    //chunk index in the pool allocator
    using ChunkID = uint32_t;

    // base class for pool allocator
    class BasePoolAllocator
    {
        public:

        private:
            // data
            std::unique_ptr<uint8_t[]> data;

            size_t chunkSize = 1;
            size_t capacity = 0;
            size_t size = 0;

            //stack of all free chunks
            std::unique_ptr<ChunkID[]> freeChunks;


            




    };
} // namespace ASEgine


#endif