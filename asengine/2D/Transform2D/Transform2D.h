#ifndef __ASENGINE_TRANSFORM_2D_H
#define __ASENGINE_TRANSFORM_2D_H

#include <unordered_set>

#include "Core/Math/Vector2.h"
#include "Core/Math/Matrix3x3.h"

#include "ECS/Component.h"
#include "ECS/EntityBuilder.h"



namespace ASEngine
{
    // transfom 2d
    struct  Transform2D: public Component<Transform2D>
    {
    public:
        Transform2D() = default;
        Transform2D(const Vector2& position, const Vector2& scale, float rotation);
        ~Transform2D() {}

        Vector2 Position = Vector2::ZERO();
        Vector2 Scale = Vector2::ONE();
        float Rotation = 0.0f;

        // get local transformation matrix
        inline Matrix3x3 GetLocalTransform() const
        {
            return Matrix3x3::Transform(Position, Scale, Rotation);
        }

        // get global transformation matrix (slow try to cache it as much as possible)
        Matrix3x3 GetGlobalTransform() const;

        // get id of parent entity with transform
        inline EntityID GetParent() const
        {
            return m_ParentID;
        }

        // get set id of parent entity with transform
        void SetParent(EntityID parentID);

        // get id of owner entity
        inline EntityID GetOwner() const
        {
            return m_OwnerID;
        }

    private:
        std::unordered_set<EntityID> m_ChildIDs{}; // should have the transform component
        std::vector<EntityBuilder> m_ChildBuilders = {}; //
        friend class Serializer;

        EntityID m_ParentID = CHUNK_NULL;
        EntityID m_OwnerID = CHUNK_NULL; // id of owner entity

        void OnCreate(EntityID entityID) override;
        void OnDestroy() override;
    };
} // namespace ASEngine


#endif // __ASENGINE_TRANSFORM_2D_H
