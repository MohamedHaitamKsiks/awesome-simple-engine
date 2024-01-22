#include "Texture.h"
#include "Renderer/Renderer.h"

namespace ASEngine
{
    Texture::Texture()
    {
    }

    Texture::~Texture()
    {
        if (m_TextureID != CHUNK_NULL)
        {
            TextureManager *textureManager = Renderer::GetTextureManager();
            textureManager->Destroy(m_TextureID);
        }
    }

    bool Texture::Load(const std::string &path)
    {
        return false;
    }

    void Texture::CreateFromImage(const Image &image)
    {

    }

    const TextureInfo &Texture::GetTextureInfo() const
    {
        TextureManager* textureManager = Renderer::GetTextureManager();
        return textureManager->GetTextureInfo(m_TextureID);
    }

} // namespace ASEngine
