#include "BaseStackAllocator.h"

namespace ASEngine
{
    BaseStackAllocator::BaseStackAllocator(size_t size)
    {
        m_Data = new uint8_t[size];
        m_StackCapacity = size;
    }

    BaseStackAllocator::~BaseStackAllocator()
    {
        delete[] m_Data;
    }



    bool BaseStackAllocator::PushRaw(const uint8_t *data, size_t size)
    {
        if (m_StackPointer + size > m_StackCapacity)
            return false;
        memcpy(m_Data + m_StackPointer, data, size);
        m_StackPointer += size;
        return true;
    }

    uint8_t *BaseStackAllocator::PopRaw(size_t size)
    {
        if (size > m_StackPointer){
            m_StackPointer = 0;
            return m_Data;
        }
        
        m_StackPointer -= size;
        return m_Data + m_StackPointer;
    }

} // namespace ASEngine
