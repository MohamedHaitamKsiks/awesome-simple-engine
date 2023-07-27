#include "TextureManager.h"

namespace ASEngine
{

    TextureManager::TextureManager()
    {
    }

    TextureManager::~TextureManager()
    {
        for (auto* info: m_Textures)
        {
            GLuint texture = info->GLTexture;
            glDeleteTextures(1, &texture);
        }
    }

    TextureID TextureManager::LoadFromImage(const Image &image)
    {
        // create GL texture
        GLuint texture;
        TextureFormat format;
        // load open gl texture
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);        
        // image format
        switch (image.GetFormat())
        {
        case ImageFormat::RGBA:
            format = TextureFormat::RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixels());
            break;
        case ImageFormat::GRAYSCALE:
            format = TextureFormat::LUMINANCE;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, image.GetWidth(), image.GetHeight(), 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, image.GetPixels());
            break;
        case ImageFormat::GRAYSCALE_ALPHA:
            format = TextureFormat::LUMINANCE_ALPHA;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, image.GetWidth(), image.GetHeight(), 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, image.GetPixels());
            break;
        }

        // create texture info
        TextureInfo info
        {
            texture, 
            image.GetWidth(), 
            image.GetHeight(),
            format
        };
        // create new texture info and return the texture id
        return m_Textures.Push(info);
        
    }

    void TextureManager::BindSampler(TextureID id, SamplerSlot slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_Textures.Get(id)->GLTexture);
    }

    void TextureManager::Destroy(TextureID id)
    {
        // delete opengl texture
        GLuint texture = GetInfo(id)->GLTexture;
        glDeleteTextures(1, &texture);

        // free texture info
        m_Textures.Free(id);
    }
} // namespace ASEngine
