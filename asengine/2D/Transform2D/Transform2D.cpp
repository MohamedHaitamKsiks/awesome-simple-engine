#include "Transform2D.h"
#include "ECS/EntityManager.h"
#include "Core/Serialization/SerializeStruct.h"


namespace ASEngine
{
    ASENGINE_SERIALIZE_STRUCT(Transform2D, Position, Scale, Rotation, Entities);


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
        for(auto& builder: Entities)
        {
            EntityID childID = EntityManager::GetInstance().Create(builder);
            
            Transform2D& childTransform = EntityManager::GetInstance().GetComponent<Transform2D>(childID);
            childTransform.m_ParentID = entityID;

            m_ChildIDs.insert(entityID);
        }
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
