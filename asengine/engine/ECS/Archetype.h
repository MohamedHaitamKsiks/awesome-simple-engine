#ifndef ASENGINE_ARCHETYPE_H
#define ASENGINE_ARCHETYPE_H

#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <memory>

#include "Core/String/UniqueString.h"

#include "ComponentCollection.h"
#include "Component.h"
#include "Signature.h"
#include "ComponentManager.h"

namespace ASEngine
{

    // component index in the collection
    using ComponentIndex = uint32_t;
    constexpr const ComponentIndex COMPONENT_INDEX_NULL = UINT32_MAX; 

    // archetype: list of components that an entity have. Picture it as a type of entity.
    class Archetype
    {
    public:
        // add component to archetype
        void AddComponent(UniqueString componentName);

        // add component to archetype
        template <typename T, typename... types>
        void AddComponents()
        {
            // check if component is of component type
            static_assert(std::is_base_of_v<TComponent<T>, T>);


            // add first component
            UniqueString componentName = TComponent<T>::s_Name;
            AddComponent(componentName);

            if constexpr (sizeof...(types) > 0)
            {
                AddComponents<types...>();
            }
        }

        // get interface of component collection
        IComponentCollection& GetComponentCollection(UniqueString componentName);

        // get component collection
        template <typename T>
        ComponentCollection<T>& GetComponentCollection()
        {
            // check if component is of component type
            static_assert(std::is_base_of_v<TComponent<T>, T>);
            UniqueString componentName = TComponent<T>::GetComponentName();
            
            ComponentCollection<T>& collection = dynamic_cast<ComponentCollection<T>&>(GetComponentCollection(componentName));
            return collection;
        }

        // get signature
        inline const Signature& GetSignature() const
        {
            return m_Signature;
        }

        // add entity
        ComponentIndex AddEntity(EntityID entityID);

        // remove entity
        void RemoveEntity(EntityID entityID);

    private:
        // signature with all components that compose the archetype
        Signature m_Signature{};

        // component collections
        std::unordered_map<UniqueString, std::unique_ptr<IComponentCollection>> m_ComponentCollections;

        // entity to component
        std::vector<EntityID> m_Entities{};

        // get component index
        ComponentIndex GetComponentIndexOfEntity(EntityID entityID);
    };

} // namespace ASEngine


#endif