#ifndef __ASENGINE_OPENGL_VIEWPORT_H
#define __ASENGINE_OPENGL_VIEWPORT_H

#include "Renderer/Backend/OpenGL/OpenGL.h"
#include "Renderer/Backend/OpenGL/Texture/OpenGLTexture.h"

#include "Renderer/Viewport/Viewport.h"

namespace ASEngine
{
    class OpenGLViewport: public Viewport
    {
    public:
        OpenGLViewport() = default;
        ~OpenGLViewport();

        // get gl frame buffer
        inline GLuint GetGLFrameBufferID() const
        {
            return m_GLFrameBufferID;
        }

        // generate textures
        // void GLGenerateTextures();
        
    private:
        void CreateImp(uint32_t width, uint32_t height, size_t textureCount);
        GLuint m_GLFrameBufferID = 0;
    
    };
} // namespace ASEngine


#endif // __ASENGINE_OPENGL_VIEWPORT_H