#include "Archetype.h"


namespace ASEngine
{

    uint32_t Archetype::getSignature() const
    {
        return signature;
    }

    void Archetype::addEntity(Entity entity)
    {
        for (auto pair: componentCollections)
        {
            std::shared_ptr<BaseComponentCollection> collection = pair.second;
            ComponentIndex componentIndex = collection->alloc();
            entities[entity] = componentIndex;
        }
    }

    void Archetype::removeEntity(Entity entity)
    {
        for (auto pair : componentCollections)
        {
            std::shared_ptr<BaseComponentCollection> collection = pair.second;
            ComponentIndex componentIndex = entities[entity];
            collection->free(componentIndex);
        }
        entities.erase(entity);
    }

} // namespace ASEngine
