#ifndef __ASENGINE_SPRITE_H
#define __ASENGINE_SPRITE_H

#include "2D/Quad2D/Quad2D.h"
#include "2D/Transform2D/Transform2D.h"
#include "Core/Math/Matrix3x3.h"
#include "Core/Math/Vector2.h"

#include "Renderer/Texture/Texture.h"
#include "Renderer/Material/Material.h"

#include "Resource/ResourceRef.h"
#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"
#include "Resource/ResourceSerialization.h"

#include "API/API.h"

namespace ASEngine
{
    class ASENGINE_API Sprite: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(Sprite);
    ASENGINE_SERIALIZE_RESOURCE(Sprite);
    public:
        ~Sprite() {}

        // create sprite from texture and frames
        void Create(const ResourceRef<Texture> &texture, uint32_t hframes, uint32_t vframes , const Vector2 &offset);

        // create sprite from texture and frames with a material
        void Create(const ResourceRef<Texture> &texture, uint32_t hframes, uint32_t vframes , const Vector2 &offset, const ResourceRef<Material>& material);

        // get number of vertical frames
        inline uint32_t GetVFrames() const
        {
            return m_VFrames;
        }

        // get number of horizontal frames
        inline uint32_t GetHFrames() const
        {
            return m_HFrames;
        }

        // get sprite texture
        inline const ResourceRef<Texture>& GetTexture() const
        {
            return m_Texture;
        }

        // sprite material
        inline const ResourceRef<Material>& GetMaterial() const
        {
            return m_Material;
        }

        // get offset
        inline const Vector2& GetOffset() const
        {
            return m_Offset;
        }

        // create quad
        void CreateQuad2D(Quad2D& quad2D, const Matrix3x3& transform, uint32_t hframe, uint32_t vframe, const Color& modulate, const Vector2& offset = Vector2::ZERO()) const;

        // create and return quad
        Quad2D CreateQuad2D(const Matrix3x3& transform, uint32_t hframe, uint32_t vframe, const Color& modulate) const;
    private:
        uint32_t m_HFrames = 0;
        uint32_t m_VFrames = 0;

        Vector2 m_SpriteSize = Vector2::ZERO();

        ResourceRef<Texture> m_Texture = ResourceRef<Texture>::NONE();
        ResourceRef<Material> m_Material = ResourceRef<Material>::NONE();

        Vector2 m_Offset = Vector2::ZERO();
        Matrix3x3 m_OffsetTransform = Matrix3x3::IDENTITY();
    };
} // namespace ASEngine

#endif // __ASENGINE_SPRITE_H
