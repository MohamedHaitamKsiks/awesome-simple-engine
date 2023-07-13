#ifndef ASENGINE_ARCHETYPE_H
#define ASENGINE_ARCHETYPE_H

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>

#include "../String/UniqueString.h"

#include "Component.h"

namespace ASEngine
{
    // component collection vector for now
    template <typename T>
    using ComponentCollection = std::vector<T>;

    // component index in the collection
    using ComponentIndex = uint32_t;

    // archetype name
    using ArchetypeName = UniqueStringID;

    // archetype: list of components that an entity have. Picture it as a type of entity.
    class Archetype
    {
    public:
        // add component to archetype
        template <typename T, typename... types>
        void addComponents()
        {
            // check if component is of component type
            static_assert(std::is_base_of_v<Component<T>, T>);

            // compute signature
            uint32_t signature = T::signature;
            if constexpr (sizeof...(types) > 0)
            {
                signature *= getSignature<types...>();
            }

        };

        // get component collection
        template <typename T>
        ComponentCollection<T>& getComponentCollection()
        {
            return nullptr;
        };

        // get signature
        uint32_t getSignature() const;
        
        // add entity
        void addEntity(Entity entity);

        // remove entity
        void removeEntity(Entity entity);

        
    private:
        // signature with all components that compose the archetype
        uint32_t signature = 1;

        // component collections
        std::unordered_map<UniqueStringID, std::shared_ptr<void>> componentCollections = {};

        // entity to component
        std::unordered_map<Entity, ComponentIndex> entities;
    };
} // namespace ASEngine


#endif