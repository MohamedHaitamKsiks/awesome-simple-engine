#ifndef __ASENGINE_MALLOC_ALLOCATOR_H
#define __ASENGINE_MALLOC_ALLOCATOR_H

#include <cstdlib>
#include <memory>
#include "API/API.h"

namespace ASEngine
{
    template <typename T>
    struct ASENGINE_API MallocAllocator
    {
        typedef T value_type;
        inline T* allocate(const size_t n) const
        {
            if (n == 0)
                return nullptr;

            return reinterpret_cast<T *>(malloc(n * sizeof(T)));
        }

        inline void deallocate(T* p, size_t n) const
        {
            free(p);
        }
    };
} // namespace ASEngine


#endif // __ASENGINE_MALLOC_ALLOCATOR_H