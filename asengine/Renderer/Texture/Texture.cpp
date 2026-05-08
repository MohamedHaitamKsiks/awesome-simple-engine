#include "Texture.h"
#include "Resource/ResourceRefSerialization.h"
#include "Core/Serialization/SerializeEnum.h"
#include "Core/Serialization/SerializeStruct.h"

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

    ASENGINE_SERIALIZE_ENUM(TextureColorFormat,
        NONE,
        RGBA,
        RGBA_32F
    )

    ASENGINE_SERIALIZE_STRUCT(TextureFromImageInfo,
        Filter,
        RepeatMode,
        Mipmaps
    )

    template <>
    void  Serializer::Deserialize(const Json &object, Texture &dest)
    {
        TextureFromImageInfo info{};
        
        // load png
        std::string imagePath = object.at("ImagePath").get<std::string>();
        info.ImageTexture.LoadPNG(imagePath);
        
        // deserialize other infos
        Deserialize(object, info);

        // create texture from image
        dest.Create(info);
    }

    template <>
    Json  Serializer::Serialize(const Texture &value)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Texture);


    void Texture::Create(const TextureInfo &info)
    {
        m_Info = info;
        CreateEmptyImp(info);
    }

    void Texture::Create(const TextureFromImageInfo &info)
    {
        // save data
        m_Info.Width = info.ImageTexture.GetWidth();
        m_Info.Height = info.ImageTexture.GetHeight();

        m_Info.Mipmaps = info.Mipmaps;
        m_Info.RepeatMode = info.RepeatMode;
        m_Info.Filter = info.Filter;

        m_Info.ColorFormat = TextureColorFormat::RGBA;

        CreateImp(info);
    }

} // namespace ASEngine
