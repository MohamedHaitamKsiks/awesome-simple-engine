#include "OpenGLBuffer.h"

namespace ASEngine
{
    OpenGLBuffer::~OpenGLBuffer()
    {
    }

    void OpenGLBuffer::CreateImp(BufferType type)
    {
        // get buffer type
        switch (type)
        {
        case BufferType::ARRAY:
            /* code */
            break;
        case BufferType::INDEX:
            break;
        default:
            break;
        }
    }

    void OpenGLBuffer::SetDataImp(const ByteBuffer &data)
    {
    }

} // namespace ASEngine
