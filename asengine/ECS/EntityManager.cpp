#include "EntityManager.h"
#include "Archetype.h"
#include "ArchetypeManager.h"

#include "Core/Debug/Debug.h"

namespace ASEngine
{
    void EntityManager::Init()
    {
        m_DestroyQueue.reserve(UINT16_MAX);
    }

    void EntityManager::Terminate()
    {
        DestroyAll();
        CleanDestroyQueue();
        m_Entities.Clear();
    }

    EntityID EntityManager::Create(const EntityBuilder &builder)
    {
        // archetype owner   
        Archetype* archetype = builder.m_Archetype;
        
        // craete entity id
        EntityID entityID = m_Entities.Allocate();
        EntityData& data = m_Entities.Get(entityID);
        data.ArchetypeOwner = archetype;
        data.IsDestroyed = false;
        data.Persistent = builder.GetPersistant();

        ComponentIndex index = archetype->AddEntity(entityID);
        data.Index = index;

        for (const auto& [componentName, componentValue]: builder.GetComponents())
        {
            auto& collection = archetype->GetComponentCollection(componentName);
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

    AbstractComponent &EntityManager::GetComponent(UniqueString componentName, EntityID entityID)
    {
        ASENGINE_ASSERT(!m_Entities.IsFree(entityID), "EntityID not found");

        auto &entityData = m_Entities.Get(entityID);
        IComponentCollection &collection = entityData.ArchetypeOwner->GetComponentCollection(componentName);

        return collection.ComponentAt(entityData.Index);
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
        auto& archetypesToClean = ArchetypeManager::GetInstance().GetArchetypes();
        // clean archetypes
        for (auto& [signature, archetype]: archetypesToClean)
        {
            archetype.RemoveDestroyedEntites();
        }

        // remove entity datas
        for (auto entityID: m_DestroyQueue)
        {
            m_Entities.Free(entityID);
        }
        
        m_DestroyQueue.clear();
    }


} // namespace ASEngine
