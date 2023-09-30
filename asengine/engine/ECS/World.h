#ifndef ASENGINE_WORLD_H
#define ASENGINE_WORLD_H

#include <memory>
#include <vector>

#include "Core/InputSystem/InputEvent.h"
#include "Core/Memory/PoolAllocator.h"
#include "Core/Memory/DynamicArray.h"
#include "Core/Singleton/Singleton.h"

#include "Entity.h"
#include "EntityData.h"
#include "EntityBuilder.h"

#include "Component.h"
#include "ComponentManager.h"

#include "Archetype.h"
#include "ArchetypeManager.h"

#include "System.h"
#include "SystemManager.h"

#include "Signature.h"

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
       
        // renderer the world
        static inline void Render2D()
        {
            SystemManager::Render2D();
        }

        // update the world
        static inline void Update(float delta)
        {
            if (GetSingleton()->m_IsFirstFrame)
            {
                SystemManager::Create();
                GetSingleton()->m_IsFirstFrame = false;
            }

            SystemManager::Update(delta);
            GetSingleton()->CleanDestroyQueue();
        }

        // process input
        static inline void ProcessInputEvent(const InputEvent& event)
        {
            SystemManager::ProcessInputEvent(event);
        }

        // destroy all
        static inline void DestroyAll()
        {
            GetSingleton()->IDestroyAll();
        }

    private:
        TPoolAllocator<EntityData> m_Entities{UINT16_MAX};
        TDynamicArray<Entity> m_DestroyQueue{};
        bool m_IsFirstFrame = true;

        // clear destroy queue executed at the end of the frame to delete
        void CleanDestroyQueue();

        // internal singleton functions

        // create entity
        Entity ICreate(EntityBuilder &builder);

        // destroy entity
        void IDestroy(Entity entity);

        void IDestroyAll();

    };


} // namespace ASENGINE

#endif