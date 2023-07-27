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

    void World::Update(float delta)
    {
        SystemManager::Update(delta);
        GetSingleton()->CleanDestroyQueue();
    }

    Entity World::ICreate(std::shared_ptr<Archetype> archetype)
    {
        // create entity
        EntityData data;
        data.ArchetypeOwner = archetype.get();
        data.IsDestroyed = false;

        Entity createdEntity = m_Entities.Push(data);

        // add entity to archetype
        archetype->AddEntity(createdEntity);

        return createdEntity;
    };

    void World::IDestroy(Entity entity)
    {
        EntityData* data = m_Entities.Get(entity);
        if (data->IsDestroyed)
            return;
        //queue entity to destroy
        data->IsDestroyed = true;
        m_DestroyQueue.push_back(entity);
    }
    
    void World::CleanDestroyQueue()
    {
        for (auto entity: m_DestroyQueue)
        {
            EntityData *data = m_Entities.Get(entity);
            auto* archetype = data->ArchetypeOwner;
            archetype->RemoveEntity(entity);
            m_Entities.Free(entity);
        }
        m_DestroyQueue.clear();
    }

} // namespace ASEngine
