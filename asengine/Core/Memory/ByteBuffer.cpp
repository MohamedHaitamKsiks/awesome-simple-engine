#include "ByteBuffer.h"

#include <cstring>
#include <cstdlib>


namespace ASEngine
{
    ByteBuffer::ByteBuffer(size_t size)
    {
        SetData(nullptr, size);
    }

    ByteBuffer::ByteBuffer(const void *data, size_t size)
    {
        SetData(data, size);
    }

    ByteBuffer::ByteBuffer(const ByteBuffer &buffer)
    {
        Copy(buffer);
    }

    ByteBuffer &ByteBuffer::operator=(const ByteBuffer &buffer)
    {
        Copy(buffer);
        return *this;
    }

    ByteBuffer::ByteBuffer(ByteBuffer &&buffer)
    {
        Move(buffer);
    }

    ByteBuffer &ByteBuffer::operator=(ByteBuffer &&buffer)
    {
        Move(buffer);
        return *this;
    }

    ByteBuffer::~ByteBuffer()
    {
        if(m_Data)
            free(m_Data);
    }

    void ByteBuffer::SetDataAt(const void *data, size_t size, size_t offset)
    {
        size_t requiredSize = offset + size;
        if (requiredSize > m_Size)
        {
            if (m_Data)
            {
                m_Data = realloc(m_Data, requiredSize);
            }
            else
            {
                m_Data = malloc(requiredSize);
            }
            m_Size = requiredSize;
        }

        if (data)
            memcpy(reinterpret_cast<char*>(m_Data) + offset, data, size);
    }

    void ByteBuffer::Copy(const ByteBuffer &buffer)
    {
        if (m_Data)
        {
            free(m_Data);
            m_Size = 0;
        }

        SetData(buffer.GetData(), buffer.GetSize());
    }

    void ByteBuffer::Move(ByteBuffer &buffer)
    {
        m_Data = buffer.m_Data;
        m_Size = buffer.m_Size;

        buffer.m_Data = nullptr;
        buffer.m_Size = 0;
    }

} // namespace ASEngine

