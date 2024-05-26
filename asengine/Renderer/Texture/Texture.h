#ifndef __ASENGINE_TEXTURE_H
#define __ASENGINE_TEXTURE_H

#include "Image.h"

#include "Resource/ResourceRef.h"
#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"

namespace ASEngine
{
    // texture format
    enum class TextureFormat
    {
        NONE = 0,
        RGBA,
        LUMINANCE,
        LUMINANCE_ALPHA
    };

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

    // abstract texture (needs to be implemented depending on api)
    class Texture: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(Texture);
    public:
        // create texture from image
        void Create(const Image& image, TextureFormat format, TextureFilter filter, TextureRepeatMode repeat);

        // get texture filter
        inline TextureFilter GetFilter() const
        {
            return m_Filter;
        }

        // get texture format
        inline TextureFormat GetFormat() const
        {
            return m_Format;
        }

        // get texture repeat mode
        inline TextureRepeatMode GetRepeatMode() const
        {
            return m_RepeatMode;
        }

        // get width
        uint32_t GetWidth() const
        {
            return m_Width;
        }

        // get height
        uint32_t GetHeight() const
        {
            return m_Height;
        }
    protected:
        // api implemetation for create from imagev
        virtual void CreateImp(const Image &image, TextureFormat format, TextureFilter filter, TextureRepeatMode repeat) = 0;

    private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        
        TextureFilter m_Filter = TextureFilter::NONE;
        TextureFormat m_Format = TextureFormat::NONE;
        TextureRepeatMode m_RepeatMode = TextureRepeatMode::NONE;
    }; 
} // namespace ASEngine


#endif // __ASENGINE_TEXTURE_H