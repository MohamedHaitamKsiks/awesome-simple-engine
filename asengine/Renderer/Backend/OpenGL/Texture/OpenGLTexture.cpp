#include "OpenGLTexture.h"

namespace ASEngine
{
    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_GLTextureID);
    }

    void OpenGLTexture::CreateImp(const Image &image, TextureFilter filter, TextureRepeatMode repeat)
    {
        // generate gl texture
        GLuint textureID = GLGenerateTexture(filter, repeat);

        // set data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixels().GetData());

        // done
        m_GLTextureID = textureID;
    }

    void OpenGLTexture::CreateEmptyImp(uint32_t width, uint32_t height, TextureFilter filter, TextureRepeatMode repeat)
    {
        // generate gl texture
        GLuint textureID = GLGenerateTexture(filter, repeat);

        // allocate space
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        // done
        m_GLTextureID = textureID;
    }

    void OpenGLTexture::GenerateMipmapsImp()
    {
        glBindTexture(GL_TEXTURE_2D, m_GLTextureID);
        glGenerateMipmap(GL_TEXTURE_2D);

        TextureFilter filter = GetFilter();
        GLUpdateTextureFilter(filter);
    }

    GLuint OpenGLTexture::GetGLTextureFilter(TextureFilter filter, bool mipmaps)
    {
        ASENGINE_ASSERT(filter != TextureFilter::NONE, "texture filter is NONE?");

        GLuint glFilter;
        switch (filter)
        {
        case TextureFilter::LINEAR:
            glFilter = mipmaps? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR;
            break;
        
        case TextureFilter::NEAREST:
            glFilter = GL_NEAREST;
            break;
        default:
            Debug::Warning("Unsupported TextureFilter");
            glFilter = mipmaps? GL_NEAREST_MIPMAP_NEAREST :  GL_NEAREST;
            break;
        }

        return glFilter;
    }

    void OpenGLTexture::GLUpdateTextureFilter(TextureFilter filter, bool mipmaps)
    {
        GLuint glFilter = GetGLTextureFilter(filter, mipmaps);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFilter);
    }

    GLuint OpenGLTexture::GetGLTextureRepeatMode(TextureRepeatMode repeat)
    {
        ASENGINE_ASSERT(repeat != TextureRepeatMode::NONE, "TextureRepeatMode is NONE?");
        
        GLuint glRepeatMode;
        switch (repeat)
        {
            case TextureRepeatMode::REPEAT:
                glRepeatMode = GL_REPEAT;
                break;
            case TextureRepeatMode::CLAMP:
                glRepeatMode = GL_CLAMP_TO_EDGE;
                break;
            default: 
                Debug::Warning("Unsupported TextureRepeatMode");
                glRepeatMode = GL_REPEAT;
                break;
        }

        return glRepeatMode;
    }

    GLuint OpenGLTexture::GLGenerateTexture(TextureFilter filter, TextureRepeatMode repeat)
    {
        // create opengl texture
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // set filter
        GLUpdateTextureFilter(filter);

        // repeat mode
        GLuint glRepeatMode = GetGLTextureRepeatMode(repeat);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glRepeatMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glRepeatMode);

        return textureID;
    }

} // namespace ASEngine
