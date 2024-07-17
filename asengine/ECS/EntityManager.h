#ifndef __ASENGINE_EntityManager_H
#define __ASENGINE_EntityManager_H

#include <memory>
#include <vector>

#include "Core/Memory/PoolAllocator.h"
#include "Core/Singleton/Singleton.h"

#include "Entity.h"
#include "EntityData.h"
#include "EntityBuilder.h"
#include "Component.h"

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
        void Init() override;

        // clean up
        void Terminate() override;

        // create entity
        EntityID Create(const EntityBuilder& builder);

        // destroy entity
        void Destroy(EntityID entity);

        // get component 
        AbstractComponent& GetComponent(UniqueString componentName, EntityID entityID);
       
        // get component template
        template<typename ComponentType>
        ComponentType& GetComponent(EntityID entityID)
        {
            ASENGINE_ASSERT(!m_Entities.IsFree(entityID), "EntityID not found");

            auto& entityData = m_Entities.Get(entityID);
            ComponentCollection<ComponentType>& collection = entityData.ArchetypeOwner->GetComponentCollection<ComponentType>();
        
            return collection[entityData.Index];
        }

        // destroy all
        void DestroyAll();

        // clear destroy queue executed at the end of the frame to delete
        void CleanDestroyQueue();

    private:
        PoolAllocator<EntityData> m_Entities{};
        std::vector<EntityID> m_DestroyQueue{};

        friend class Archetype;
    };


} // namespace ASENGINE

#endif