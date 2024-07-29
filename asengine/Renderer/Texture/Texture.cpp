#include "Texture.h"
#include "Resource/ResourceRefSerialization.h"
#include "Core/Serialization/SerializeEnum.h"

ASENGINE_SERIALIZE_RESOURCE_REF(Texture);

namespace ASEngine
{
    ASENGINE_SERIALIZE_ENUM(TextureFilter, 
        NONE,
        NEAREST,
        LINEAR
    );

    ASENGINE_SERIALIZE_ENUM(TextureRepeatMode,
        NONE,
        REPEAT,
        CLAMP
    )

    template <>
    void  Serializer::Deserialize(const Json &object, Texture &dest)
    {
        // load png
        std::string imagePath = object.at("ImagePath").get<std::string>();
        Image image{};
        image.LoadPNG(imagePath);

        // get filter
        TextureFilter filter = TextureFilter::NONE;
        Serializer::Deserialize(object.at("Filter"), filter);

        // get repeat mode
        TextureRepeatMode repeat = TextureRepeatMode::NONE;
        Serializer::Deserialize(object.at("RepeatMode"), repeat);

        dest.Create(image, filter, repeat);
    }

    template <>
    Json  Serializer::Serialize(const Texture &value)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Texture);

    void Texture::Create(uint32_t width, uint32_t height, TextureFilter filter, TextureRepeatMode repeat)
    {
        // save data
        m_Width = width;
        m_Height = height;
        m_Filter = filter;
        m_RepeatMode = repeat;

        // call implementation
        CreateEmptyImp(width, height, filter, repeat);
    }

    void Texture::Create(const Image &image, TextureFilter filter, TextureRepeatMode repeat)
    {
        // save data
        m_Width = image.GetWidth();
        m_Height = image.GetHeight();
        m_Filter = filter;
        m_RepeatMode = repeat;

        // call implementation
        CreateImp(image, filter, repeat);
    }
} // namespace ASEngine
