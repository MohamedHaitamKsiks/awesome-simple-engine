#include "Transform2D.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "ECS/EntityBuilder.h"
#include "ECS/EntityManager.h"
#include <vector>


namespace ASEngine
{
    template<>
    void Serializer::Deserialize(const Json& object, Transform2D& dest)
    {
        // deserialize fields
        Serializer::Deserialize(object.at("Position"), dest.Position);
        Serializer::Deserialize(object.at("Scale"), dest.Scale);

        // angles are readed as degree
        float rotationDeg = 0.0f;
        Serializer::Deserialize(object.at("Rotation"), rotationDeg);
        dest.Rotation = rotationDeg * Math::PI / 180.0f;

        // deserialize entity builders
        if (object.find("Entities") != object.end())
        {
            Serializer::Deserialize(object.at("Entities"), dest.m_ChildBuilders);
        }
    }

    template<>
    Json Serializer::Serialize(const Transform2D& dest)
    {
        return Json({});
    }

    Transform2D::Transform2D(const Vector2 &position, const Vector2 &scale, float rotation): Position(position), Scale(scale), Rotation(rotation)
    {
    }

    void Transform2D::SetParent(EntityID parentID)
    {
        // unset old parent
        if (m_ParentID != CHUNK_NULL)
        {
            Transform2D &currentParentTransform = EntityManager::GetInstance().GetComponent<Transform2D>(m_ParentID);
            currentParentTransform.m_ChildIDs.erase(m_OwnerID);
        }

        Transform2D& parentTransform = EntityManager::GetInstance().GetComponent<Transform2D>(parentID);
        parentTransform.m_ChildIDs.insert(m_OwnerID);

        m_ParentID = parentID;
    }

    void Transform2D::OnCreate(EntityID entityID)
    {
        m_OwnerID = entityID;
        for(auto& builder: m_ChildBuilders)
        {
            EntityID childID = EntityManager::GetInstance().Create(builder);

            Transform2D& childTransform = EntityManager::GetInstance().GetComponent<Transform2D>(childID);
            childTransform.m_ParentID = entityID;

            m_ChildIDs.insert(entityID);
        }

        // destroy child builders to free up space
        std::vector<EntityBuilder> emptyBuilder;
        m_ChildBuilders.swap(emptyBuilder);
    }

    void Transform2D::OnDestroy()
    {
        // unset old parent
        if (m_ParentID != CHUNK_NULL)
        {
            Transform2D &currentParentTransform = EntityManager::GetInstance().GetComponent<Transform2D>(m_ParentID);
            currentParentTransform.m_ChildIDs.erase(m_OwnerID);
        }

        // remove childs
        for (EntityID childID: m_ChildIDs)
        {
            EntityManager::GetInstance().Destroy(childID);
        }
    }

    Matrix3x3 Transform2D::GetGlobalTransform() const
    {
        if (m_ParentID == CHUNK_NULL)
            return GetLocalTransform();

        Transform2D &parentTransform = EntityManager::GetInstance().GetComponent<Transform2D>(m_ParentID);
        return parentTransform.GetGlobalTransform() * GetLocalTransform();
    }

} // namespace ASEngine
