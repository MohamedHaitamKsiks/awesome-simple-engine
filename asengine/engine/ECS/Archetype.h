#ifndef ASENGINE_ARCHETYPE_H
#define ASENGINE_ARCHETYPE_H

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>

#include "engine/Memory/DynamicArray.h"
#include "engine/String/UniqueString.h"

#include "Component.h"
#include "ComponentManager.h"

namespace ASEngine
{
    // component collection vector for now
    template <typename T>
    using ComponentCollection = TDynamicArray<T>;
    using BaseComponentCollection = DynamicArray;

    // component index in the collection
    using ComponentIndex = uint32_t;

    // archetype: list of components that an entity have. Picture it as a type of entity.
    class Archetype
    {
    public:
        // set component to archetype
        template <typename T, typename... types>
        void AddComponents();

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

        // get component index
        ComponentIndex GetComponentIndexOfEntity(Entity entity);

        // get component of entity
        template <typename T>
        T& GetComponentOfEntity(Entity entity);

        // set component (s)of entity
        template <typename T, typename... Types>
        void SetComponentOfEntity(Entity entity, const T &firstComponent, const Types &...args);

        // set component(s)
        template <typename T, typename... Types>
        void SetComponent(ComponentIndex index, const T& firstComponent, const Types&... args);

        // get component 
        template <typename T>
        T& GetComponent(ComponentIndex index);

        // remove entity
        void RemoveEntity(Entity entity);

    private:
        // signature with all components that compose the archetype
        uint32_t m_Signature = 1;

        // component collections
        std::unordered_map<UniqueString, std::shared_ptr<BaseComponentCollection>> m_ComponentCollections = {};

        // entity to component
        TDynamicArray<Entity> m_Entities{UINT16_MAX};
    };

    // implementations
    // add component implementation
    template <typename T, typename... types>
    void Archetype::AddComponents()
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);

        // get component info
        UniqueString componentName = Component<T>::s_Name;
        uint32_t componentSignature = Component<T>::s_Signature;

        // check if component isnot added
        if (m_Signature % componentSignature != 0)
        {
            m_Signature *= componentSignature;
            std::shared_ptr<BaseComponentCollection> collection{new ComponentCollection<T>(UINT16_MAX)};
            m_ComponentCollections[componentName] = collection;
        }

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
        static_assert(std::is_base_of_v<Component<T>, T>);

        UniqueString componentName = Component<T>::s_Name;

        auto baseComponentCollection = m_ComponentCollections[componentName];
        std::shared_ptr<ComponentCollection<T>> collection = std::static_pointer_cast<ComponentCollection<T>>(baseComponentCollection);
        
        return *collection;
    };

    // get component of entity implementation
    template <typename T>
    T& Archetype::GetComponentOfEntity(Entity entity)
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);
        ComponentCollection<T>& collection = GetComponentCollection<T>();

        // get index
        ComponentIndex index = GetComponentIndexOfEntity(entity);
        if (index == UINT32_MAX)
            return nullptr;

        // return component pointer
        return collection[index];
    }

    template <typename T>
    T& Archetype::GetComponent(ComponentIndex index)
    {
        // get collection
        static_assert(std::is_base_of_v<Component<T>, T>);
        ComponentCollection<T> &collection = GetComponentCollection<T>();
        return collection[index];
    }

    // set component (s)of entity
    template <typename T, typename... Types>
    void Archetype::SetComponentOfEntity(Entity entity, const T &firstComponent, const Types &...args)
    {
        ComponentIndex index = GetComponentIndexOfEntity(entity);
        if (index == UINT32_MAX)
            return;
        SetComponent(index, firstComponent, args...);
    }

    // set component(s)
    template <typename T, typename... Types>
    void Archetype::SetComponent(ComponentIndex index, const T &firstComponent, const Types &...args)
    {
        T& component = GetComponent<T>(index);
        memcpy(&component, &firstComponent, sizeof(T));

        if constexpr (sizeof...(args) > 0)
        {
            SetComponent(index, args...);
        }
    }
} // namespace ASEngine


#endif