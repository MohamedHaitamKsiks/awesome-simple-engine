#include "EntityManager.h"
#include "Archetype.h"
#include "ArchetypeManager.h"

#include "Core/Debug/Debug.h"

namespace ASEngine
{

    void EntityManager::Terminate()
    {
        DestroyAll();
        CleanDestroyQueue();
        m_Entities.Clear();
    }

    EntityID EntityManager::Create(const EntityBuilder &builder)
    {
        // archetype owner
        const auto& signature = builder.GetSignature();
        
        Archetype& archetype = ArchetypeManager::GetInstance().GetArchetype(signature);
        
        EntityData data;
        data.ArchetypeOwner = &archetype;
        data.IsDestroyed = false;
        data.Persistent = builder.GetPersistant();

        EntityID entityID = m_Entities.Push(data);
        ComponentIndex index = archetype.AddEntity(entityID);

        for (const auto& [componentName, componentValue]: builder.GetComponents())
        {
            auto& collection = archetype.GetComponentCollection(componentName);
            auto& component = collection.ComponentAt(index);

            component.Copy(*componentValue);
            component.OnCreate(entityID);
        }

        return entityID;
        
    };
    
    void EntityManager::Destroy(EntityID entityID)
    {
        EntityData& data = m_Entities.Get(entityID);
        if (data.IsDestroyed)
        {
            Debug::Error("Warning: Entity", entityID, "already removed!");
            return;
        }

        //queue entity to destroy
        data.IsDestroyed = true;
        m_DestroyQueue.push_back(entityID);
    }

    void EntityManager::DestroyAll()
    {
        size_t entityCounter = 0;
        for (EntityID entityID = 0; entityID < m_Entities.GetCapacity() && entityCounter < m_Entities.GetSize(); entityID++ )
        {
            if (m_Entities.IsFree(entityID)) continue;

            // get entity data
            auto& entityData = m_Entities.Get(entityID);

            // destroy entity
            if (!entityData.Persistent)
            {
                Destroy(entityID);
            }

            entityCounter++;
        }
    }

    void EntityManager::CleanDestroyQueue()
    {
        for (auto entity: m_DestroyQueue)
        {
            EntityData& data = m_Entities.Get(entity);
            auto* archetype = data.ArchetypeOwner;
            archetype->RemoveEntity(entity);
            m_Entities.Free(entity);
        }
        
        m_DestroyQueue.clear();
    }


} // namespace ASEngine
