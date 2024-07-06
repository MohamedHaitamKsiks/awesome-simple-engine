#include "Viewport.h"
#include "Resource/ResourceRefSerialization.h"

ASENGINE_SERIALIZE_RESOURCE_REF(Viewport);

namespace ASEngine
{
    template <>
    void Serializer::Deserialize(const Json &object, Viewport &dest)
    {
        // get width
        uint32_t width = 0;
        Serializer::Deserialize(object.at("Width"), width);

        // height
        uint32_t height = 0;
        Serializer::Deserialize(object.at("Height"), height);

        // create
        dest.Create(width, height);
    }

    template <>
    Json Serializer::Serialize(const Viewport &value)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Viewport);

    void Viewport::Create(uint32_t width, uint32_t height, size_t textureCount)
    {
        // save data
        m_Width = width;
        m_Height = height;

        // create texture
        for (size_t i = 0; i < textureCount; i++)
        {
            ResourceRef<Texture> texture = Texture::GetResourceClass().New();
            texture->Create(width, height, TextureFilter::NEAREST, TextureRepeatMode::CLAMP);            
        
            m_Textures.push_back(texture);
        }

        // call implementation
        CreateImp(width, height, textureCount);
    }

} // namespace ASEngine
