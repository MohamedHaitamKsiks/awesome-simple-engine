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

        inline GLuint GetGLTextureType() const
        {
            return GL_TEXTURE_2D;
        }

        void GLBind();

    private:
        GLuint m_GLTextureID;
        GLuint m_GLTextureInternalFormat;
        GLuint m_GLFilter;
        GLuint m_GLRepeatMode;

        void CreateImp(const TextureFromImageInfo &info) override;
        void CreateEmptyImp(const TextureInfo &info) override;

        // get corresponding GLuint for filter
        static GLuint GetGLTextureFilter(TextureFilter filter, bool mipmaps = false);
        
        // get corresponding GLuint for repeat mode
        static GLuint GetGLTextureRepeatMode(TextureRepeatMode repeatMode);

        // get corresponding GLuint for color format
        static GLuint GetGLTextureColorFormat(TextureColorFormat format);

        // generate opengl texture
        void GLGenerateTexture(uint32_t witdth, uint32_t height, const void* data);
    };
} // namespace ASEngine

#endif // __ASENGINE_OPENGL_TEXTURE_H