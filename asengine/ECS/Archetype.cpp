#include "Archetype.h"
#include "Core/Error/Assertion.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "ComponentClass.h"

namespace ASEngine
{

    void Archetype::AddComponent(UniqueString componentName)
    {
        ASENGINE_ASSERT(m_Signature.count(componentName) == 0, "Component Already Exists");
        
        m_Signature.emplace(componentName);
        
        // create component collection
        IComponentClass& componentClass = ComponentManager::GetInstance().GetComponentClass(componentName);
        std::unique_ptr<IComponentCollection> collection{componentClass.CreateComponentCollection()};
        m_ComponentCollections[componentName] = std::move(collection);
    
    }

    IComponentCollection& Archetype::GetComponentCollection(UniqueString componentName)
    {
        ASENGINE_ASSERT(m_ComponentCollections.find(componentName) != m_ComponentCollections.end(), "ComponentType Not Found!");
        return *m_ComponentCollections[componentName];
    }

    ComponentIndex Archetype::AddEntity(EntityID entityID)
    {
        ComponentIndex index;
        for (auto& [componentName, collection]: m_ComponentCollections)
            index = collection->Add();
        
        m_Entities.push_back(entityID);
        return index;
    }

    void Archetype::RemoveDestroyedEntites()
    {
        // get entity data
        auto& entityManager = EntityManager::GetInstance();
        auto& entitiesData = entityManager.m_Entities;
        
        // get component indices keep
        std::vector<ComponentIndex> indices{};
        indices.reserve(m_Entities.size());

        // entities to keep
        std::vector<EntityID> entities{};
        entities.reserve(m_Entities.size());

        for (EntityID entityID: m_Entities)
        {
            EntityData& entityData = entitiesData.Get(entityID);
            if (entityData.IsDestroyed)
                continue;

            indices.push_back(entityData.Index);
            entities.push_back(entityID);
        }

        // clean component collections
        for (auto &[componentName, collection] : m_ComponentCollections)
            collection->KeepOnly(indices);

        // update entity comoponent index
        for (ComponentIndex index = 0; index < entities.size(); index++)
        {
            EntityID entityID = entities[index];

            EntityData &entityData = entitiesData.Get(entityID);
            entityData.Index = index;
        }

        // set new entities
        m_Entities.swap(entities);
    }

    /*void Archetype::RemoveEntity(EntityID entityID)
    {
        // find component index
        ComponentIndex index = GetComponentIndexOfEntity(entityID);
        ASENGINE_ASSERT(index != COMPONENT_INDEX_NULL, "Can't remove inexisting Entity");

        // remove components
        for (auto& [componentName, collection] : m_ComponentCollections)
            collection->Remove(index);
        
        m_Entities.erase(m_Entities.begin() + index);
    }*/

} // namespace ASEngine
