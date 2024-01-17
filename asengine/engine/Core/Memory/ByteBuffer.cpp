#include "ByteBuffer.h"

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

    ByteBuffer::~ByteBuffer()
    {
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
        }

        if (data)
            memcpy(m_Data, data, size);
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

} // namespace ASEngine

