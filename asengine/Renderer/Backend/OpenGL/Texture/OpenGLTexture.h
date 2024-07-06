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
        void CreateEmptyImp(uint32_t width, uint32_t height , TextureFilter filter, TextureRepeatMode repeat) override;

        // get corresponding GLuint for filter
        static GLuint GetGLTextureFilter(TextureFilter filter);
        
        // get corresponding GLuint for repeat mode
        static GLuint GetGLTextureRepeatMode(TextureRepeatMode repeat);
        
        // generate opengl texture
        static GLuint GLGenerateTexture(TextureFilter filter, TextureRepeatMode repeat);

    };
} // namespace ASEngine

#endif // __ASENGINE_OPENGL_TEXTURE_H