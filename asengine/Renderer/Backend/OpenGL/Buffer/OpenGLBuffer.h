#ifndef __ASENGINE_OPENGL_BUFFER_H
#define __ASENGINE_OPENGL_BUFFER_H

#include "Renderer/Backend/OpenGL/OpenGL.h"
#include "Renderer/Buffer/Buffer.h"

namespace ASEngine
{
    class OpenGLBuffer: public Buffer
    {
    public:
        // destructor
        OpenGLBuffer();
        ~OpenGLBuffer();

        inline GLuint GetGLBufferID() const
        {
            return m_GLBufferID;
        } 

        inline GLuint GetGLBufferType() const
        {
            return m_GLBufferType;
        }

        inline void GLBind()
        {
            glBindBuffer(m_GLBufferType, m_GLBufferID);
        }

    private:
        // opengl buffer id
        GLuint m_GLBufferID = 0;

        // opengl buffer type
        GLuint m_GLBufferType = 0;

        // implementations
        void CreateImp(BufferType type) override;
        void SetDataImp(const void *data, size_t size) override;
    };
} // namespace ASEngine


#endif // __ASENGINE_OPENGL_BUFFER_H