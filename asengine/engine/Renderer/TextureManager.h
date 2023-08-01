#ifndef ASENGINE_TEXTURE_MANAGER_H
#define ASENGINE_TEXTURE_MANAGER_H

#include "engine/Memory/PoolAllocator.h"
#include "engine/Resource/Image.h"
#include "engine/Singleton/Singleton.h"

#include "GraphicsAPI.h"

namespace ASEngine
{
    // texture id
    using TextureID = ChunkID;

    // sampler 
    using SamplerSlot = int;

    // texture format
    enum class TextureFormat
    {
        RGBA,
        LUMINANCE,
        LUMINANCE_ALPHA
    };

    // texture information
    struct TextureInfo
    {
        GLuint GLTexture;
        int Width;
        int Height;
        TextureFormat Format;
    };

    // texture manager
    class TextureManager:public Singleton<TextureManager>
    {
    public:
        TextureManager();
        ~TextureManager();

        friend class Texture;

    private:
        // list of textures 
        TPoolAllocator<TextureInfo> m_Textures{UINT16_MAX};

        // load texture form image
        TextureID LoadFromImage(const Image &image);

        // bind sampler
        void BindSampler(TextureID id, SamplerSlot slot);

        // destroy texture
        void Destroy(TextureID id);

        // get texture info for texture id
        inline TextureInfo& GetInfo(TextureID id) { return m_Textures.Get(id); };
    };
    
} // namespace ASEngine


#endif // ASENGINE_TEXTURE_MANAGER_H