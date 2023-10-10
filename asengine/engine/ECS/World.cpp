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
        DestroyAll();
        CleanDestroyQueue();

        ComponentManager::Terminate();
        SystemManager::Terminate();
        ArchetypeManager::Terminate();
    }

    Entity World::ICreate(EntityBuilder &builder)
    {
        // archetype owner
        Signature signature{};
        for (auto componentName: builder.m_ComponentNames)
        {
            signature.emplace(componentName);
        }
        auto* archetype = ArchetypeManager::GetArchetype(signature);
        
        EntityData data;
        data.ArchetypeOwner = archetype;
        data.IsDestroyed = false;
        data.Persistent = builder.Persistent;

        Entity entity = m_Entities.Push(data);
        ComponentIndex index = archetype->AddEntity(entity);

        for (int i = 0; i < builder.m_ComponentNames.GetSize(); i++)
        {
            auto componentName = builder.m_ComponentNames[i];
            auto componentValue = builder.m_Components[i];

            auto* component = archetype->GetComponent(componentName, index);
            ComponentManager::CopyComponent(componentName, component, componentValue);
            component->Owner = entity;
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

    void World::IDestroyAll()
    {
        size_t entityCounter = 0;
        for (Entity entity = 0; entity < m_Entities.GetCapacity() && entityCounter < m_Entities.GetSize(); entity++ )
        {
            if (m_Entities.IsFree(entity)) continue;

            // get entity data
            auto& entityData = m_Entities.Get(entity);

            // destroy entity
            if (!entityData.Persistent)
            {
                IDestroy(entity);
            }
        }
    }

    void World::IUpdate(float delta)
    {
        if (m_IsFirstFrame)
        {
            SystemManager::Create();
            m_IsFirstFrame = false;
        }

        // call fixed steps
        m_FixedTimer += delta;
        while (m_FixedTimer >= Time::FixedTimeStep)
        {
            SystemManager::FixedUpdate(Time::FixedTimeStep);
            m_FixedTimer -= Time::FixedTimeStep;
        }

        SystemManager::Update(delta * Time::TimeScale);
        CleanDestroyQueue();
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
