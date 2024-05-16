#ifndef ASENGINE_EntityManager_H
#define ASENGINE_EntityManager_H

#include <memory>
#include <vector>

#include "Core/Memory/PoolAllocator.h"
#include "Core/Singleton/Singleton.h"

#include "Entity.h"
#include "EntityData.h"
#include "EntityBuilder.h"

#include "System.h"

#include "Signature.h"

namespace ASEngine
{
    // context of ecs: the EntityManager where all the entities exists
    class EntityManager: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(EntityManager);

    public:
        // clean up
        void Terminate();

        // create entity
        EntityID Create(const EntityBuilder& builder);

        // destroy entity
        void Destroy(EntityID entity);
       
        // destroy all
        void DestroyAll();

        // clear destroy queue executed at the end of the frame to delete
        void CleanDestroyQueue();

    private:
        PoolAllocator<EntityData> m_Entities{UINT16_MAX};
        std::vector<EntityID> m_DestroyQueue{};
        bool m_IsFirstFrame = true;
    };


} // namespace ASENGINE

#endif