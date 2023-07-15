#ifndef ASENGINE_ARCHETYPE_H
#define ASENGINE_ARCHETYPE_H

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>

#include "engine/Memory/BasePoolAllocator.h"
#include "engine/Memory/PoolAllocator.h"
#include "engine/String/UniqueString.h"

#include "Component.h"
#include "ComponentManager.h"

namespace ASEngine
{
    // component collection vector for now
    template <typename T>
    using ComponentCollection = PoolAllocator<T>;
    using BaseComponentCollection = BasePoolAllocator;

    // component index in the collection
    using ComponentIndex = ChunkID;

    // archetype: list of components that an entity have. Picture it as a type of entity.
    class Archetype
    {
    public:
        // set component to archetype
        template <typename T, typename... types>
        void addComponents();

        // get component collection
        template <typename T>
        ComponentCollection<T>& getComponentCollection();

        // get signature
        uint32_t getSignature() const;

    
        // add entity
        void addEntity(Entity entity);

        // get component of entity
        template <typename T>
        T* getComponentOfEntity(Entity entity);

        // remove entity
        void removeEntity(Entity entity);

        private:
        // signature with all components that compose the archetype
        uint32_t signature = 1;

        // component collections
        std::unordered_map<UniqueStringID, std::shared_ptr<BaseComponentCollection>> componentCollections = {};

        // entity to component
        std::unordered_map<Entity, ComponentIndex> entities = {};
    };

    // implementations
    // add component implementation
    template <typename T, typename... types>
    void Archetype::addComponents()
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);

        // get component info
        UniqueString componentName = Component<T>::name;
        uint32_t componentSignature = Component<T>::signature;

        // check if component isnot added
        if (signature % componentSignature != 0)
        {
            signature *= componentSignature;
            std::shared_ptr<BaseComponentCollection> collection{new ComponentCollection<T>(UINT16_MAX)};
            componentCollections[componentName.getId()] = collection;
        }

        if constexpr (sizeof...(types) > 0)
        {
            addComponents<types...>();
        }
    };

    //get component collection
    template <typename T>
    ComponentCollection<T>& Archetype::getComponentCollection()
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);

        UniqueString componentName = Component<T>::name;

        auto baseComponentCollection = componentCollections[componentName.getId()];
        std::shared_ptr<ComponentCollection<T>> componentCollection = std::static_pointer_cast<ComponentCollection<T>>(baseComponentCollection);
        return *componentCollection;
    };

    // get component of entity implementation
    template <typename T>
    T* Archetype::getComponentOfEntity(Entity entity)
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);

        ComponentIndex index = entities[entity];
        auto &collection = getComponentCollection<T>();

        return collection.get(index);
    }

} // namespace ASEngine


#endif