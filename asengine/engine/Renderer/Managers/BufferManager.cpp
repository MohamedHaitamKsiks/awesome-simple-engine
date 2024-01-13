#define OPENGL
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

        default:
            throw BufferInvalidTypeException();
        }

        glGenBuffers(1, &bufferInfo.GLBufferID);
    #endif // OPENGL

        m_BufferInfos.Push(bufferInfo);
    }

    void BufferManager::Allocate(BufferID bufferID, size_t size, const void *data)
    {
        auto &bufferInfo = m_BufferInfos.Get(bufferID);
    
    #ifdef OPENGL
        glBindBuffer(bufferInfo.GLBufferType, bufferInfo.GLBufferID);
        glBufferData(bufferInfo.GLBufferType, size, data, GL_DYNAMIC_DRAW);
    #endif // OPENGL

        bufferInfo.Size = size;        
    }

    void BufferManager::SetData(BufferID bufferID, size_t offset, size_t size, const void *data)
    {
        const auto& bufferInfo = GetBufferInfo(bufferID);
        
        // check offset and size in buffer's range
        if (offset + size > bufferInfo.Size)
            throw BufferOutOfRangeException();
        
    #ifdef OPENGL
        glBindBuffer(bufferInfo.GLBufferType, bufferInfo.GLBufferID);
        glBufferSubData(bufferInfo.GLBufferType, offset, size, data);
    #endif // OPENGl
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
