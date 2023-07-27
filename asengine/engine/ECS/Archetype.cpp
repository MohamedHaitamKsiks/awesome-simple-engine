#include "Archetype.h"

namespace ASEngine
{

    uint32_t Archetype::GetSignature() const
    {
        return m_Signature;
    }

    void Archetype::AddEntity(Entity entity)
    {
        for (auto pair: m_ComponentCollections)
        {
            std::shared_ptr<BaseComponentCollection> collection = pair.second;
            ComponentIndex componentIndex = collection->Alloc();
            m_Entities[entity] = componentIndex;
        }
    }

    void Archetype::RemoveEntity(Entity entity)
    {
        for (auto pair : m_ComponentCollections)
        {
            std::shared_ptr<BaseComponentCollection> collection = pair.second;
            ComponentIndex componentIndex = m_Entities[entity];
            collection->Free(componentIndex);
        }
        m_Entities.erase(entity);
    }

} // namespace ASEngine
