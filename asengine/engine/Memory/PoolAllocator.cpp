#include "PoolAllocator.h"


namespace ASEngine 
{

    template <typename T>
    void PoolAllocator<T>::Free(ChunkID index) 
    {
        if (!IsUsed(index))
            return;
        //call destructor of the object to simulate it's destruction
        //we need to do that since freeing objects from poolallocator doesn't destroy them from memory
        //but since it's logically free we can call the destructor and simulate to make it equivilent to delete operator
        Get(index)->~T();
        // call base function
        BasePoolAllocator::Free(index);
    }

    template <typename T>
    ChunkID PoolAllocator<T>::Push(const T& value)
    {
        ChunkID id = Alloc();
        T* allocatedValue = Get(id);
        *allocatedValue = value;
        return id;
    }
    
    template <typename T>
    T *PoolAllocator<T>::Get(ChunkID index)
    {
        return (T*) GetRaw(index);
    }

    template <typename T>
    void PoolAllocator<T>::InitializePoolValues()
    {   
        T baseValue{};

        for (size_t i = 0; i < m_Capacity; i++)
        {
            T* currentPtr = Get((ChunkID) i);
            *currentPtr = baseValue;
        }
    }

} // namespace ASEngine
