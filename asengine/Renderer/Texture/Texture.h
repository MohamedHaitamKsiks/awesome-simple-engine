#ifndef __ASENGINE_TEXTURE_H
#define __ASENGINE_TEXTURE_H

#include "Core/Math/Vector2.h"
#include "Image.h"

#include "Resource/ResourceRef.h"
#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"
#include "Resource/ResourceSerialization.h"



namespace ASEngine
{
    // filter
    enum class TextureFilter
    {
        NONE = 0,
        NEAREST,
        LINEAR
    };

    // repeat mode
    enum class TextureRepeatMode
    {
        NONE = 0,
        REPEAT,
        CLAMP
    };

    enum class TextureColorFormat
    {
        NONE = 0,
        RGBA,
        RGBA_32F // HDR
    };          

    // texture info
    struct TextureInfo
    {
        uint32_t            Width           = 0;
        uint32_t            Height          = 0;
        TextureFilter       Filter          = TextureFilter::NONE;
        TextureRepeatMode   RepeatMode      = TextureRepeatMode::NONE;
        TextureColorFormat  ColorFormat     = TextureColorFormat::NONE;
        bool                Mipmaps         = false;
    };

    // texture from image info
    struct TextureFromImageInfo
    {
        Image               ImageTexture{};
        TextureFilter       Filter          = TextureFilter::NONE;
        TextureRepeatMode   RepeatMode      = TextureRepeatMode::NONE;
        bool                Mipmaps         = false;
    };

    // abstract texture (needs to be implemented depending on api)
    class  Texture : public Resource
    {
    ASENGINE_DEFINE_RESOURCE(Texture);
    ASENGINE_SERIALIZE_RESOURCE(Texture);
    public:
        // create texture memory but with no value
        void Create(const TextureInfo& info);

        // create texture from image
        void Create(const TextureFromImageInfo& info);

        // get texture filter
        inline TextureFilter GetFilter() const
        {
            return m_Info.Filter;
        }

        // get texture repeat mode
        inline TextureRepeatMode GetRepeatMode() const
        {
            return m_Info.RepeatMode;
        }

        // get texture intnal color forrmat
        inline TextureColorFormat GetColorFromat() const
        {
            return m_Info.ColorFormat;
        }


        // get width
        inline uint32_t GetWidth() const
        {
            return m_Info.Width;
        }

        // get height
        inline uint32_t GetHeight() const
        {
            return m_Info.Height;
        }

        // get size
        inline Vector2 GetSize() const
        {
            return Vector2(static_cast<float>(GetWidth()), static_cast<float>(GetHeight()));
        }

        inline bool HasMipmaps() const
        {
            return m_Info.Mipmaps;
        }

    protected:
        // api implemetation for create from image
        virtual void CreateImp(const TextureFromImageInfo &info) = 0;
        virtual void CreateEmptyImp(const TextureInfo &info) = 0;

    private:
        TextureInfo m_Info{};
    };
} // namespace ASEngine


#endif // __ASENGINE_TEXTURE_H
