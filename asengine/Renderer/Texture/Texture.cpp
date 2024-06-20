#include "Texture.h"
#include "Resource/ResourceRefSerialization.h"

ASENGINE_SERIALIZE_RESOURCE_REF(Texture);

namespace ASEngine
{
    template <>
    void Serializer::Deserialize(const Json &object, Texture &dest)
    {
        std::string imagePath = object.at("ImagePath").get<std::string>();
        
        Image image{};
        image.LoadPNG(imagePath);

        dest.Create(image, TextureFilter::LINEAR, TextureRepeatMode::REPEAT);
    }

    template <>
    Json Serializer::Serialize(const Texture &value)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Texture);

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
