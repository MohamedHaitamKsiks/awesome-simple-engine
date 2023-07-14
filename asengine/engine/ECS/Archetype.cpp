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
            std::shared_ptr<BaseComponentCollection> componentCollection = pair.second;
            ComponentIndex componentIndex = componentCollection->alloc();
            entities[entity] = componentIndex;
        }
    }

    void Archetype::removeEntity(Entity entity)
    {
        for (auto pair : componentCollections)
        {
            std::shared_ptr<BaseComponentCollection> componentCollection = pair.second;
            ComponentIndex componentIndex = entities[entity];
            componentCollection->free(componentIndex); 
        }
        entities.erase(entity);
    }

} // namespace ASEngine
