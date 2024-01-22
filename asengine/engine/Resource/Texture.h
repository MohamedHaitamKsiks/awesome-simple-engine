#ifndef ASENGINE_TEXTURE_H
#define ASENGINE_TEXTURE_H

#include "Renderer/Managers/TextureManager.h"
#include "Image.h"
#include "Resource.h"

namespace ASEngine
{
    // texture resource
    class Texture: public Resource
    {
    public:
        Texture();
        ~Texture();

        bool Load(const std::string& path);

        void CreateFromImage(const Image& image);

        const TextureInfo& GetTextureInfo() const;

        inline TextureID GetTextureID() const
        {
            return m_TextureID;
        };

    private:
        TextureID m_TextureID = CHUNK_NULL;
    };

} // namespace ASEngine


#endif // ASENGINE_TEXTURE_H