#include "OpenGLTexture.h"

namespace ASEngine
{
    OpenGLTexture::~OpenGLTexture()
    {
    }

    void OpenGLTexture::CreateImp(const Image &image, TextureFilter filter, TextureRepeatMode repeat)
    {
        // create opengl texture
        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        // set filter
        GLuint glFilter = GetGLTextureFilter(filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glFilter);

        // repeat mode
        GLuint glRepeatMode = GetGLTextureRepeatMode(repeat);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glRepeatMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glRepeatMode);

        // set data
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixels().GetData());

        // done
        m_GLTextureID = textureID;
    }

    GLuint OpenGLTexture::GetGLTextureFilter(TextureFilter filter)
    {
        ASENGINE_ASSERT(filter != TextureFilter::NONE, "texture filter is NONE?");

        GLuint glFilter;
        switch (filter)
        {
        case TextureFilter::LINEAR:
            glFilter = GL_LINEAR;
            break;
        
        case TextureFilter::NEAREST:
            glFilter = GL_NEAREST;
            break;
        default:
            Debug::Warning("Unsupported TextureFilter");
            glFilter = GL_NEAREST;
            break;
        }

        return glFilter;
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
                glRepeatMode = GL_CLAMP;
                break;
            default: 
                Debug::Warning("Unsupported TextureRepeatMode");
                glRepeatMode = GL_REPEAT;
                break;
        }

        return glRepeatMode;
    }

} // namespace ASEngine
