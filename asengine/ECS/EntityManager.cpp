#include "EntityManager.h"
#include "Archetype.h"
#include "ArchetypeManager.h"

#include "Core/Debug/Debug.h"
#include "ECS/ArchetypeManager.h"
#include "ECS/Signature.h"
#include <unordered_set>

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
        data.Persistent = builder.IsPersistant();
        data.Tag = builder.GetTag();

        // create entity
        ComponentIndex index = archetype->AddEntity(entityID);
        data.Index = index;

        for (const auto& [componentName, componentValue]: builder.GetComponents())
        {
            auto& collection = archetype->GetComponentCollection(componentName);
            auto& component = collection.ComponentAt(index);

            component.Copy(*componentValue);
            component.OnCreate(entityID);
        }

        // add tag
        if (builder.HasTag())
        {
            UniqueString tag = builder.GetTag();
            ASENGINE_ASSERT(m_TaggedEntities.find(tag) == m_TaggedEntities.end(), "Tag already exists");
            m_TaggedEntities[tag] = entityID;
        }

        return entityID;

    };

    void EntityManager::Destroy(EntityID entityID)
    {
        EntityData& data = m_Entities.Get(entityID);
        if (data.IsDestroyed)
            return;

        // queue entity to destroy
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
            if (entityData.IsDestroyed)
                continue;

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
        // retrieve archetypes to clean
        std::unordered_set<Signature> archetypesToClean = {};
        for (auto entityID: m_DestroyQueue)
        {
            EntityData& data = m_Entities.Get(entityID);
            data.ArchetypeOwner->RemoveEntity(entityID);

            archetypesToClean.insert(m_Entities.Get(entityID).ArchetypeOwner->GetSignature());
        }

        // clean archetypes
        for (const auto& signature: archetypesToClean)
        {
            ArchetypeManager::GetInstance().GetArchetype(signature).RemoveDestroyedEntites();
        }

        // remove entity datas
        for (auto entityID: m_DestroyQueue)
        {
            // remove tag if exits
            UniqueString tag = GetTag(entityID);
            if (m_TaggedEntities.find(tag) != m_TaggedEntities.end())
            {
                m_TaggedEntities.erase(tag);
            }

            m_Entities.Free(entityID);
        }

        m_DestroyQueue.clear();
    }

    EntityID EntityManager::GetEntityByTag(UniqueString tag) const
    {
        if (m_TaggedEntities.find(tag) != m_TaggedEntities.end())
        {
            return m_TaggedEntities.at(tag);
        }

        return CHUNK_NULL;
    }


} // namespace ASEngine
