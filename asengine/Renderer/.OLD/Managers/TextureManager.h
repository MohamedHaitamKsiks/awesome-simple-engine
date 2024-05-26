#ifndef __ASENGINE_TEXTURE_MANAGER_H
#define __ASENGINE_TEXTURE_MANAGER_H

#include "Core/Memory/PoolAllocator.h"
#include "Core/Singleton/Singleton.h"

#include "Resource/Image.h"

#include "Renderer/GraphicsAPI.h"

namespace ASEngine
{
    // texture format
    enum class TextureFormat
    {
        RGBA,
        LUMINANCE,
        LUMINANCE_ALPHA
    };

    // filter
    enum class TextureFilter
    {
        NEAREST,
        LINEAR
    };

    // texture information
    struct TextureInfo
    {
    #pragma region OPENGL_SPECIFICATION
        GLuint GLTexture;
#pragma endregion OPENGL_SPECIFICATION
        int Width;
        int Height;
        TextureFormat Format;
        TextureFilter Filter;
    };

    // texture id
    using TextureID = ChunkID;

    // texture manager
    class TextureManager
    {
    public:
        TextureManager() {};
        ~TextureManager() {};

        // Create texture form image
        TextureID CreateFromImage(const Image &image, TextureFilter filter = TextureFilter::NEAREST);

        // get texture info
        inline const TextureInfo& GetTextureInfo(TextureID textureID) const
        {
            return m_TextureInfos.Get(textureID);
        }

        // destroy texture
        void Destroy(TextureID textureID);

    private:
        // list of textures 
        TPoolAllocator<TextureInfo> m_TextureInfos{UINT16_MAX};
    };
    
} // namespace ASEngine


#endif // __ASENGINE_TEXTURE_MANAGER_H