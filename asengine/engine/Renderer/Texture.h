#ifndef ASENGINE_TEXTURE_H
#define ASENGINE_TEXTURE_H

#include "GraphicsAPI.h"
#include "engine/Memory/PoolAllocator.h"
#include "engine/Resource/Image.h"

#include "TextureManager.h"

namespace ASEngine
{
    // texture abstraction
    class Texture
    {
    public:
        Texture() {};
        Texture(TextureID id) { m_Id = id; };

        // compare texures
        inline friend bool operator==(const Texture& a, const Texture& b)
        {
            return a.m_Id == b.m_Id;
        }

        inline friend bool operator!=(const Texture &a, const Texture &b)
        {
            return a.m_Id != b.m_Id;
        }

        // load texture from image
        static inline Texture LoadFromImage(const Image& image)
        {
            return Texture(TextureManager::GetSingleton()->LoadFromImage(image));
        };

        // bind texture to sampler slot
        void inline BindSampler(SamplerSlot slot)
        {
            TextureManager::GetSingleton()->BindSampler(m_Id, slot);
        };

        // destroy texture
        void inline Destroy() 
        {
            TextureManager::GetSingleton()->Destroy(m_Id);
        };

        // get widths
        int inline GetWidth() const
        {
            return TextureManager::GetSingleton()->GetInfo(m_Id).Width;
        };

        // get widths
        int inline GetHeight() const
        {
            return TextureManager::GetSingleton()->GetInfo(m_Id).Height;
        };

        // get widths
        TextureFormat inline GetFormat() const
        {
            return TextureManager::GetSingleton()->GetInfo(m_Id).Format;
        };

    private:
        // texture id
        TextureID m_Id = CHUNK_NULL;
    };

    // null texture
    static const Texture TEXTURE_NULL = Texture(CHUNK_NULL);

} // namespace ASEngine


#endif // ASENGINE_TEXTURE_H