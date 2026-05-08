#include "Viewport.h"
#include "Core/Serialization/SerializeStruct.h"
#include "Resource/ResourceRefSerialization.h"

ASENGINE_SERIALIZE_RESOURCE_REF(Viewport);

namespace ASEngine
{
    ASENGINE_SERIALIZE_STRUCT(ViewportInfo, 
        Width, 
        Height, 
        Samples
    )

    template <>
    void  Serializer::Deserialize(const Json &object, Viewport &dest)
    {
        ViewportInfo info{};
        info.TextureCount = 1;
        
        Serializer::Deserialize(object, info);

        // create
        dest.Create(info);
    }

    template <>
    Json  Serializer::Serialize(const Viewport &value)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Viewport);

    void Viewport::Create(uint32_t width, uint32_t height, size_t textureCount)
    {
        ViewportInfo info{
            .Width = width,
            .Height = height,
            .TextureCount = textureCount
        };

        Create(info);
    }

    void Viewport::Create(const ViewportInfo &info)
    {
        m_Info = info;

        // create texture
        TextureInfo textureInfo{
            .Width = info.Width,
            .Height = info.Height,
            .Filter = TextureFilter::NEAREST,
            .RepeatMode = TextureRepeatMode::CLAMP,
            .ColorFormat = TextureColorFormat::RGBA,
            .Mipmaps = false,
        };

        for (size_t i = 0; i < info.TextureCount; i++)
        {
            ResourceRef<Texture> texture = Texture::GetResourceClass().New();
            texture->Create(textureInfo);

            m_Textures.push_back(texture);
        }

        CreateImp(info);
    }

} // namespace ASEngine
