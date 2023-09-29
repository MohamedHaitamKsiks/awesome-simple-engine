#include "Archetype.h"

namespace ASEngine
{

    void Archetype::AddComponent(UniqueString componentName)
    {
        uint32_t componentSignature = ComponentManager::GetSignature(componentName);
        if (m_Signature % componentSignature != 0)
        {
            m_Signature *= componentSignature;
            m_ComponentCollections[componentName] = ComponentManager::CreateComponentCollection(componentName);
        }

    }

    ComponentIndex Archetype::AddEntity(Entity entity)
    {
        ComponentIndex index;
        for (auto pair: m_ComponentCollections)
        {
            std::shared_ptr<BaseComponentCollection> collection = pair.second;
            index = collection->Add();
        }
        m_Entities.Push(entity);
        return index;
    }
    
    void Archetype::RemoveEntity(Entity entity)
    {
        // find component index
        ComponentIndex index = GetComponentIndexOfEntity(entity);
        if (index == UINT32_MAX)
            return;

        // remove components
        for (auto pair : m_ComponentCollections)
        {
            std::shared_ptr<BaseComponentCollection> collection = pair.second;
            
            Component* component = (Component*) collection->PtrAt(index);
            component->OnDestroy();

            collection->Remove(index);
        }
        m_Entities.Remove(index);
    }

    Component* Archetype::GetComponent(UniqueString componentName, ComponentIndex index)
    {
        std::shared_ptr<BaseComponentCollection> collection = m_ComponentCollections[componentName];
        return (Component*) collection->PtrAt(index);
    }

    ComponentIndex Archetype::GetComponentIndexOfEntity(Entity entity)
    {
        // find component index
        for (ComponentIndex i = 0; i < m_Entities.GetSize(); i++)
        {
            if (m_Entities[i] == entity)
            {
                return i;
            }
        }
        return UINT32_MAX;
    }


} // namespace ASEngine
