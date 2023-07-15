#include "PoolAllocator.h"


namespace ASEngine 
{

    template <typename T>
    void PoolAllocator<T>::free(ChunkID index) 
    {
        if (!isUsed(index))
            return;
        //call destructor of the object to simulate it's destruction
        //we need to do that since freeing objects from poolallocator doesn't destroy them from memory
        //but since it's logically free we can call the destructor and simulate to make it equivilent to delete operator
        get(index)->~T();
        // call base function
        BasePoolAllocator::free(index);
    }
    
    template <typename T>
    T *PoolAllocator<T>::get(ChunkID index)
    {
        return (T*) getRaw(index);
    }

    template <typename T>
    void PoolAllocator<T>::initializePoolValues()
    {   
        T baseValue{};

        for (size_t i = 0; i < capacity; i++)
        {
            T* currentPtr = get((ChunkID) i);
            *currentPtr = baseValue;
        }
    }

} // namespace ASEngine
