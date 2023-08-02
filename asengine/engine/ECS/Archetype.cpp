#include "Archetype.h"

namespace ASEngine
{

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
            collection->Remove(index);
        }
        m_Entities.Remove(index);
    }

} // namespace ASEngine
