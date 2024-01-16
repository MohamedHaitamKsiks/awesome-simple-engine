#include "BufferManager.h"

namespace ASEngine
{
    BufferManager::BufferManager()
    { 
    }

    BufferID BufferManager::Create(BufferType bufferType)
    {
        BufferInfo bufferInfo{};
        bufferInfo.Type = bufferType;

    #ifdef OPENGL
        switch (bufferInfo.Type)
        {
        case BufferType::ARRAY:
            bufferInfo.GLBufferType = GL_ARRAY_BUFFER;
            break;

        case BufferType::INDEX:
            bufferInfo.GLBufferType = GL_ELEMENT_ARRAY_BUFFER;
            break;
        
        case BufferType::UNIFORM_BUFFER:
            bufferInfo.GLBufferType = GL_UNIFORM_BUFFER:
            break;

        default:
            throw BufferInvalidTypeException();
        }

        glGenBuffers(1, &bufferInfo.GLBufferID);
    #endif // OPENGL

        m_BufferInfos.Push(bufferInfo);
    }

    void BufferManager::SetData(BufferID bufferID, const ByteBuffer &buffer)
    {
        auto &bufferInfo = m_BufferInfos.Get(bufferID);

#ifdef OPENGL
        glBindBuffer(bufferInfo.GLBufferType, bufferInfo.GLBufferID);
        glBufferData(bufferInfo.GLBufferType, buffer.GetSize(), buffer.GetData(), GL_DYNAMIC_DRAW);
#endif // OPENGL

        bufferInfo.Size = buffer.GetSize();
    }

    void BufferManager::Delete(BufferID bufferID)
    {
        auto& bufferInfo = GetBufferInfo(bufferID);

    #ifdef OPENGL
        glDeleteBuffers(1, &bufferInfo.GLBufferID);
    #endif // OPENGL

        m_BufferInfos.Free(bufferID);
    }

} // namespace ASEngine
