#include "TextureManager.h"

namespace ASEngine
{
    TextureID TextureManager::CreateFromImage(const Image &image, TextureFilter filter)
    {
        // create texture info
        TextureInfo textureInfo{};
        textureInfo.Width = image.GetWidth();
        textureInfo.Height = image.GetHeight();
        textureInfo.Filter = filter;

    #ifdef OPENGL
        // create GL texture
        GLuint texture;
        // load open gl texture
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // image format
        switch (image.GetFormat())
        {
        case ImageFormat::RGBA:
            textureInfo.Format = TextureFormat::RGBA;
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.GetWidth(), image.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixels());
            break;
        case ImageFormat::GRAYSCALE:
            textureInfo.Format = TextureFormat::LUMINANCE;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, image.GetWidth(), image.GetHeight(), 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, image.GetPixels());
            break;
        case ImageFormat::GRAYSCALE_ALPHA:
            textureInfo.Format = TextureFormat::LUMINANCE_ALPHA;
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, image.GetWidth(), image.GetHeight(), 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, image.GetPixels());
            break;
        }
        textureInfo.GLTexture = texture;
    
    #endif // OPENGL
        // create new texture info and return the texture id
        return m_TextureInfos.Push(textureInfo);
    }

    void TextureManager::Destroy(TextureID textureID)
    {
    #ifdef OPENGL
        auto& textureInfo = GetTextureInfo(textureID);
        glDeleteTextures(1, &textureInfo.GLTexture);
    #endif // OPENGL

        m_TextureInfos.Free(textureID);
    }
} // namespace ASEngine
