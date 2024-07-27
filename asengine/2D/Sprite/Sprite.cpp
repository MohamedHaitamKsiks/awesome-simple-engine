#include "Sprite.h"
#include "2D/Quad2D/Quad2D.h"
#include "2D/Renderer2D/Renderer2D.h"
#include "Core/Math/Matrix3x3.h"
#include "Core/Math/Vector2.h"
#include "Core/Serialization/Serializer.h"
#include "Renderer/Material/Material.h"
#include "Resource/ResourceRefSerialization.h"

ASENGINE_SERIALIZE_RESOURCE_REF(Sprite);

namespace ASEngine
{
    template <>
    void Serializer::Deserialize(const Json &object, Sprite &dest)
    {
        // get texture
        ResourceRef<Texture> texture;
        Serializer::Deserialize(object.at("Texture"), texture);

        // get frames
        uint32_t hframes = 0;
        Serializer::Deserialize(object.at("HFrames"), hframes);
        uint32_t vframes = 0;
        Serializer::Deserialize(object.at("VFrames"), vframes);

        // get offset
        Vector2 offset;
        Serializer::Deserialize(object.at("Offset"), offset);

        // is offset relative to center
        bool relativeToCenter = false;
        Serializer::Deserialize(object.at("RelativeToCenter"), relativeToCenter);

        // set origin to center
        if (relativeToCenter)
        {
            float frameWidth = static_cast<float>(texture->GetWidth()) / static_cast<float>(hframes);
            float frameHeight = static_cast<float>(texture->GetHeight()) / static_cast<float>(vframes);

            offset += Vector2(frameWidth, frameHeight) * 0.5f;
        }

        // get material
        ResourceRef<Material> material = Renderer2D::GetInstance().GetDefaultMaterial();
        if (object.find("Material") != object.end())
        {
            Serializer::Deserialize(object.at("Material"), material);
        }

        // create sprite
        dest.Create(texture, hframes, vframes, offset, material);

    }

    template <>
    Json Serializer::Serialize(const Sprite &value)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Sprite);

    void Sprite::Create(const ResourceRef<Texture>& texture, uint32_t hframes, uint32_t vframes, const Vector2& offset,  const ResourceRef<Material>& material)
    {
        // save sprite data
        m_Texture = texture;

        m_HFrames = hframes;
        m_VFrames = vframes;

        m_Offset = offset;
        m_OffsetTransform = Matrix3x3::Translate(offset * -1.0f);

        m_SpriteSize = Vector2(static_cast<float>(texture->GetWidth()) / static_cast<float>(hframes), static_cast<float>(texture->GetHeight()) / static_cast<float>(vframes));

        // create default material
        ResourceRef<Material> spriteMaterial = material->Clone();
        spriteMaterial->SetShaderParam("Texture", texture);

        m_Material = spriteMaterial;
    }

    void Sprite::Create(const ResourceRef<Texture>& texture, uint32_t hframes, uint32_t vframes, const Vector2& offset)
    {
        Create(texture, hframes, vframes, offset, Renderer2D::GetInstance().GetDefaultMaterial());
    }

    void Sprite::CreateQuad2D(Quad2D& quad2D, const Matrix3x3& transform, uint32_t hframe, uint32_t vframe, const Color& modulate, const Vector2& offset) const
    {
        quad2D.Create(
            m_SpriteSize,
            transform,
            modulate,
            Vector2(static_cast<float>(hframe) / static_cast<float>(m_HFrames), static_cast<float>(vframe) / static_cast<float>(m_VFrames)),
            Vector2(static_cast<float>(hframe + 1) / static_cast<float>(m_HFrames), static_cast<float>(vframe + 1) / static_cast<float>(m_VFrames)),
            offset + m_Offset * -1.0f
        );
    }

    Quad2D Sprite::CreateQuad2D(const Matrix3x3& transform, uint32_t hframe, uint32_t vframe, const Color& modulate) const
    {
        Quad2D quad2D;
        CreateQuad2D(quad2D, transform, hframe, vframe, modulate);
        return quad2D;
    }
} // namespace ASEngine
