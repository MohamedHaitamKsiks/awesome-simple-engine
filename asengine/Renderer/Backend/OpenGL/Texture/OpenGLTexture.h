#ifndef __ASENGINE_OPENGL_TEXTURE_H
#define __ASENGINE_OPENGL_TEXTURE_H

#include "Renderer/Backend/OpenGL/OpenGL.h"
#include "Renderer/Texture/Texture.h"

namespace ASEngine
{

    // opengl implementation of texture
    class OpenGLTexture: public Texture
    {
    public:
        OpenGLTexture() = default;
        ~OpenGLTexture();

        inline GLuint GetGLTextureID() const
        {
            return m_GLTextureID;
        }

    private:
        GLuint m_GLTextureID;
       
        void CreateImp(const Image &image, TextureFilter filter, TextureRepeatMode repeat) override;
    
        static GLuint GetGLTextureFilter(TextureFilter filter);
        static GLuint GetGLTextureRepeatMode(TextureRepeatMode repeat);
    };
} // namespace ASEngine

#endif // __ASENGINE_OPENGL_TEXTURE_H