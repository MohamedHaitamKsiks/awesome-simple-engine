#include "OpenGLBuffer.h"

namespace ASEngine
{
    OpenGLBuffer::OpenGLBuffer()
    {
    }

    OpenGLBuffer::~OpenGLBuffer()
    {
        glDeleteBuffers(1, &m_GLBufferID);
    }

    void OpenGLBuffer::CreateImp(BufferType type)
    {
        // get buffer type
        switch (type)
        {
        case BufferType::ARRAY:
            m_GLBufferType = GL_ARRAY_BUFFER;
            break;
        case BufferType::INDEX:
            m_GLBufferType = GL_ELEMENT_ARRAY_BUFFER;
            break;
        case BufferType::UNIFORM_BUFFER:
            m_GLBufferType = GL_UNIFORM_BUFFER;
        default:
            break;
        }

        glGenBuffers(1, &m_GLBufferID);
    }

    void OpenGLBuffer::SetDataImp(const void *data, size_t size)
    {
        glBindBuffer(m_GLBufferType, m_GLBufferID);
        glBufferData(m_GLBufferType, size, data, GL_DYNAMIC_DRAW);
    }

} // namespace ASEngine
