#ifndef __ASENGINE_ARCHETYPE_H
#define __ASENGINE_ARCHETYPE_H

#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <memory>
#include <tuple>

#include "Core/String/UniqueString.h"

#include "ComponentCollection.h"
#include "Component.h"
#include "Signature.h"
#include "ComponentManager.h"

#include "API/API.h"

namespace ASEngine
{

    // component index in the collection
    using ComponentIndex = uint32_t;
    constexpr const ComponentIndex COMPONENT_INDEX_NULL = UINT32_MAX; 

    // archetype: list of components that an entity have. Picture it as a type of entity.
    class ASENGINE_API Archetype
    {
    public:
        // add component to archetype
        void AddComponent(UniqueString componentName);

        // add component to archetype
        template <typename T, typename... types>
        void AddComponents()
        {
            // check if component is of component type
            static_assert(std::is_base_of_v<Component<T>, T>);


            // add first component
            UniqueString componentName = Component<T>::GetName();
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
            static_assert(std::is_base_of_v<Component<T>, T>);
            UniqueString componentName = Component<T>::GetName();
            
            ComponentCollection<T>& collection = static_cast<ComponentCollection<T>&>(GetComponentCollection(componentName));
            return collection;
        }

        // get signature
        inline const Signature& GetSignature() const
        {
            return m_Signature;
        }

        // add entity
        ComponentIndex AddEntity(EntityID entityID);

        // destroyed entities
        void RemoveDestroyedEntites();

        // get entity count
        inline size_t GetSize() const
        {
            return m_Entities.size();
        }

        // get component collections tuple
        template<typename T, typename... types>
        inline constexpr std::tuple<ComponentCollection<T> &, ComponentCollection<types> &...> GetComponentCollections()
        {
            std::tuple<ComponentCollection<T> &, ComponentCollection<types> &...> collections(this->template GetComponentCollection<T>(), this->template GetComponentCollection<types>()...);
            return collections;
        }

    private:
        // signature with all components that compose the archetype
        Signature m_Signature{};

        // component collections
        std::map<UniqueString, std::unique_ptr<IComponentCollection>> m_ComponentCollections;

        // entity to component
        std::vector<EntityID> m_Entities{};
    };

} // namespace ASEngine


#endif