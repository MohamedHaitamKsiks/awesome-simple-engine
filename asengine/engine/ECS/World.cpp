#include "World.h"

namespace ASEngine
{
    World::World()
    {
        ComponentManager::Init();
        SystemManager::Init();
        ArchetypeManager::Init();
    }

    World::~World()
    {
        ComponentManager::Terminate();
        SystemManager::Terminate();
        ArchetypeManager::Terminate();
    }

    Entity World::ICreate(EntityBuilder &builder)
    {
        // archetype owner
        auto archetype = ArchetypeManager::GetArchetype(builder.m_ComponentNames);
        
        EntityData data;
        data.ArchetypeOwner = archetype.get();
        data.IsDestroyed = false;

        Entity entity = m_Entities.Push(data);
        ComponentIndex index = archetype->AddEntity(entity);

        for (int i = 0; i < builder.m_ComponentNames.GetSize(); i++)
        {
            auto componentName = builder.m_ComponentNames[i];
            auto componentValue = builder.m_Components[i];

            auto* component = archetype->GetComponent(componentName, index);
            ComponentManager::CopyComponent(componentName, component, componentValue.get());
            component->OnCreate();
        }

        return entity;
        
    };
    
    void World::IDestroy(Entity entity)
    {
        EntityData& data = m_Entities.Get(entity);
        if (data.IsDestroyed)
            return;
        //queue entity to destroy
        data.IsDestroyed = true;
        m_DestroyQueue.Push(entity);
    }
    
    void World::CleanDestroyQueue()
    {
        for (auto entity: m_DestroyQueue)
        {
            EntityData& data = m_Entities.Get(entity);
            auto* archetype = data.ArchetypeOwner;
            archetype->RemoveEntity(entity);
            m_Entities.Free(entity);
        }
        m_DestroyQueue.Clear();
    }

} // namespace ASEngine
