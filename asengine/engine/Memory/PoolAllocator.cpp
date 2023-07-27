#include "PoolAllocator.h"


namespace ASEngine 
{

    template<typename T>
    PoolAllocator<T>::~PoolAllocator()
    {
        delete[] m_Data;
    }

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
    void PoolAllocator<T>::InitializePoolValues()
    {   
        // allocate data
        m_Data = new T[m_Capacity];
    }

} // namespace ASEngine
