#ifndef ASENGINE_WORLD_H
#define ASENGINE_WORLD_H

#include <memory>
#include <vector>

#include "engine/Memory/PoolAllocator.h"
#include "engine/Singleton/Singleton.h"

#include "Entity.h"
#include "EntityData.h"

#include "Component.h"
#include "ComponentManager.h"

#include "Archetype.h"
#include "ArchetypeManager.h"

#include "System.h"
#include "SystemManager.h"

namespace ASEngine
{
    // list of all information for an entity we just created
    struct EntityCreateInfo
    {
        Entity entity;
        ComponentIndex index;
        Archetype *archetype = nullptr;
    };

    // context of ecs: the world where all the entities exists
    class World: public Singleton<World>
    {
    public: 
        // contructor
        World();

        // destructor
        ~World();

        // create entity based on an archetype
        static inline Entity Create(std::shared_ptr<Archetype> archetype) { return GetSingleton()->ICreate(archetype).entity; };
        
        // create entity based on components signature
        template<typename T, typename... types>
        static Entity Create();
        
        // create entities with components values
        template <typename T, typename... types>
        static Entity Create(T firstComponent, types... components);
       
        // set comonents of entity
        template <typename T, typename... types>
        static inline void SetComponents(Entity entity, const T& firstComponent, const types&... components);
        
        // get component of entity
        template <typename T>
        static inline T& GetComponent(Entity entity) { return GetSingleton()->IGetComponent<T>(entity); };
        
        // destroy entity
        static inline void Destroy(Entity entity) { GetSingleton()->IDestroy(entity); };
       
        // update the world
        static void Update(float delta);


    private:
        TPoolAllocator<EntityData> m_Entities{UINT16_MAX};
        TDynamicArray<Entity> m_DestroyQueue{};

        // clear destroy queue executed at the end of the frame to delete
        void CleanDestroyQueue();

        // internal singleton functions

        // create entity based on archetype
        EntityCreateInfo ICreate(std::shared_ptr<Archetype> archetype);

        // get component from an entity
        template <typename T>
        T& IGetComponent(Entity entity);

        // destroy entity
        void IDestroy(Entity entity);

    };

    // implementations

    template <typename T, typename... types>
    Entity World::Create()
    {
        // get archetype
        auto archetype = ArchetypeManager::GetArchetype<T, types...>();
        // create entity
        return Create(archetype);
    };

    template <typename T, typename... types>
    Entity World::Create(T firstComponent, types... components)
    {
        // get archetype
        auto archetype = ArchetypeManager::GetArchetype<T, types...>();
        // create entity
        EntityCreateInfo info = GetSingleton()->ICreate(archetype);
        info.archetype->SetComponent(info.index, firstComponent, components...);
        return info.entity;
    };

    template <typename T, typename... types>
    void World::SetComponents(Entity entity, const T &firstComponent, const types &...components)
    {
        EntityData& data = GetSingleton()->m_Entities.Get(entity);
        data.ArchetypeOwner->SetComponentOfEntity(entity, firstComponent, components...);
    };

    template <typename T>
    T& World::IGetComponent(Entity entity)
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);

        // get component
        auto *archetype = m_Entities.Get(entity).ArchetypeOwner;
        return archetype->GetComponentOfEntity<T>(entity);
    };

} // namespace ASENGINE

#endif