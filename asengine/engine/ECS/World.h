#ifndef ASENGINE_WORLD_H
#define ASENGINE_WORLD_H

#include <memory>
#include <vector>

#include "engine/Memory/PoolAllocator.h"
#include "engine/Memory/DynamicArray.h"

#include "engine/Singleton/Singleton.h"

#include "Entity.h"
#include "EntityData.h"
#include "EntityBuilder.h"

#include "Component.h"
#include "ComponentManager.h"

#include "Archetype.h"
#include "ArchetypeManager.h"

#include "System.h"
#include "SystemManager.h"

namespace ASEngine
{
    // context of ecs: the world where all the entities exists
    class World: public Singleton<World>
    {
    public: 
        // contructor
        World();

        // destructor
        ~World();

        // create entity
        static inline Entity Create(EntityBuilder& builder) { return GetSingleton()->ICreate(builder); }

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

        // create entity
        Entity ICreate(EntityBuilder &builder);

        // destroy entity
        void IDestroy(Entity entity);

    };


} // namespace ASENGINE

#endif