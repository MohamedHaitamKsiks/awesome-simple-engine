#include "Archetype.h"
#include "Core/Error/Assertion.h"
#include "ComponentManager.h"
#include "ComponentClass.h"

namespace ASEngine
{

    void Archetype::AddComponent(UniqueString componentName)
    {
        ASENGINE_ASSERT(m_Signature.count(componentName) == 0, "Component Already Exists");
        
        m_Signature.emplace(componentName);
        //create component collectio
        ComponentClass& componentClass = ComponentManager::GetInstance().GetComponentClass(componentName);
        std::unique_ptr<IComponentCollection> collection(componentClass.CreateComponentCollection());
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
    
    void Archetype::RemoveEntity(EntityID entityID)
    {
        // find component index
        ComponentIndex index = GetComponentIndexOfEntity(entityID);
        ASENGINE_ASSERT(index != COMPONENT_INDEX_NULL, "Can't remove inexisting Entity");

        // remove components
        for (auto& [componentName, collection] : m_ComponentCollections)
            collection->Remove(index);
        
        m_Entities.erase(m_Entities.begin() + index);
    }

    ComponentIndex Archetype::GetComponentIndexOfEntity(EntityID entityID)
    {
        // find component index
        for (ComponentIndex i = 0; i < m_Entities.size(); i++)
        {
            if (m_Entities[i] == entityID)
                return i;
        }
        return COMPONENT_INDEX_NULL;
    }


} // namespace ASEngine
