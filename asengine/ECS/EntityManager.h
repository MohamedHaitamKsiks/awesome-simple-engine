#ifndef __ASENGINE_EntityManager_H
#define __ASENGINE_EntityManager_H

#include <memory>
#include <vector>

#include "Core/Memory/PoolAllocator.h"
#include "Core/Singleton/Singleton.h"

#include "Entity.h"
#include "EntityData.h"
#include "EntityBuilder.h"

#include "System.h"

#include "Signature.h"

#include "API/API.h"

namespace ASEngine
{
    // context of ecs: the EntityManager where all the entities exists
    class ASENGINE_API EntityManager : public ISystem
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
        PoolAllocator<EntityData> m_Entities{};
        std::vector<EntityID> m_DestroyQueue{};
    };


} // namespace ASENGINE

#endif