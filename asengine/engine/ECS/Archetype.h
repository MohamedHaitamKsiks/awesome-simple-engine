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
        void AddComponents();

        // get component collection
        template <typename T>
        ComponentCollection<T>& GetComponentCollection();

        // get signature
        uint32_t GetSignature() const;

        // add entity
        void AddEntity(Entity entity);

        // get component of entity
        template <typename T>
        T* GetComponentOfEntity(Entity entity);

        // remove entity
        void RemoveEntity(Entity entity);

    private:
        // signature with all components that compose the archetype
        uint32_t m_Signature = 1;

        // component collections
        std::unordered_map<UniqueString, std::shared_ptr<BaseComponentCollection>> m_ComponentCollections = {};

        // entity to component
        std::unordered_map<Entity, ComponentIndex> m_Entities = {};
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
    T* Archetype::GetComponentOfEntity(Entity entity)
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);

        ComponentIndex index = m_Entities[entity];
        auto &collection = GetComponentCollection<T>();

        return collection.Get(index);
    }

} // namespace ASEngine


#endif