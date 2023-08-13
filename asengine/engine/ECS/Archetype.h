#ifndef ASENGINE_ARCHETYPE_H
#define ASENGINE_ARCHETYPE_H

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>

#include "Core/Memory/DynamicArray.h"
#include "Core/String/UniqueString.h"

#include "Component.h"
#include "ComponentManager.h"

namespace ASEngine
{


    // component index in the collection
    using ComponentIndex = uint32_t;

    // archetype: list of components that an entity have. Picture it as a type of entity.
    class Archetype
    {
    public:
        // add component to archetype
        template <typename T, typename... types>
        void AddComponents();

        // add component to archetype
        void AddComponent(UniqueString componentName);

        // get component collection
        template <typename T>
        ComponentCollection<T>& GetComponentCollection();


        // get signature
        inline uint32_t GetSignature() const
        {
            return m_Signature;
        }

        // add entity
        ComponentIndex AddEntity(Entity entity);

        // get component 
        template <typename T>
        T& GetComponent(ComponentIndex index);

        // get component
        Component* GetComponent(UniqueString componentName, ComponentIndex index);

        // remove entity
        void RemoveEntity(Entity entity);

    private:
        // signature with all components that compose the archetype
        uint32_t m_Signature = 1;

        // component collections
        std::unordered_map<UniqueString, std::shared_ptr<BaseComponentCollection>> m_ComponentCollections = {};

        // entity to component
        TDynamicArray<Entity> m_Entities{UINT16_MAX};

        // get component index
        ComponentIndex GetComponentIndexOfEntity(Entity entity);
    };

    // implementations
    // add component implementation
    template <typename T, typename... types>
    void Archetype::AddComponents()
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
    };

    //get component collection
    template <typename T>
    ComponentCollection<T>& Archetype::GetComponentCollection()
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<TComponent<T>, T>);

        UniqueString componentName = TComponent<T>::s_Name;

        auto baseComponentCollection = m_ComponentCollections[componentName];
        std::shared_ptr<ComponentCollection<T>> collection = std::static_pointer_cast<ComponentCollection<T>>(baseComponentCollection);
        
        return *collection;
    };

    template <typename T>
    T& Archetype::GetComponent(ComponentIndex index)
    {
        // get collection
        static_assert(std::is_base_of_v<TComponent<T>, T>);
        ComponentCollection<T> &collection = GetComponentCollection<T>();
        return collection[index];
    }

} // namespace ASEngine


#endif