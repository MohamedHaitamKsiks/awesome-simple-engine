#include "OpenGLTexture.h"

namespace ASEngine
{
    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_GLTextureID);
    }

    void OpenGLTexture::GLBind()
    {
        glBindTexture(GL_TEXTURE_2D, m_GLTextureID);
    }

    void OpenGLTexture::CreateImp(const TextureFromImageInfo &info)
    {
        // generate gl texture
        const auto& image = info.ImageTexture;
        GLGenerateTexture(image.GetWidth(), image.GetHeight(), image.GetPixels().GetData());
    }

    void OpenGLTexture::CreateEmptyImp(const TextureInfo& info)
    {
        // generate gl texture
        GLGenerateTexture(info.Width, info.Height, nullptr);
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

    GLuint OpenGLTexture::GetGLTextureColorFormat(TextureColorFormat format)
    {
        ASENGINE_ASSERT(format != TextureColorFormat::NONE, "TextureColorFormat is NONE?");

        GLuint glFormat = GL_RGBA;
        switch (format)
        {
        case TextureColorFormat::RGBA :
            glFormat = GL_RGBA;
            break;
        case TextureColorFormat::RGBA_32F:
            glFormat = GL_RGBA32F;
            break;
        default:
            break;
        }

        return glFormat;
    }

    void OpenGLTexture::GLGenerateTexture(uint32_t width, uint32_t height, const void *data)
    {
        // create opengl texture
        glGenTextures(1, &m_GLTextureID);
        GLBind();

        // get color format
        TextureColorFormat format = GetColorFromat();
        m_GLTextureInternalFormat = GetGLTextureColorFormat(format);

        // allocate data
        glTexImage2D(GL_TEXTURE_2D, 0, m_GLTextureInternalFormat, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        // geneate mipmaps
        if (HasMipmaps())
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        // set filter
        TextureFilter filter = GetFilter();
        bool mipmaps = HasMipmaps();
        m_GLFilter = GetGLTextureFilter(filter, mipmaps);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_GLFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_GLFilter);

        // repeat mode
        TextureRepeatMode repeatMode = GetRepeatMode();
        m_GLRepeatMode = GetGLTextureRepeatMode(repeatMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_GLRepeatMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_GLRepeatMode);
    }


} // namespace ASEngine
