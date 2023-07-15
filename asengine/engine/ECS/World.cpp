#include "World.h"

namespace ASEngine
{
    World::World()
    {
        ComponentManager::init();
        SystemManager::init();
        ArchetypeManager::init();
    }

    World::~World()
    {
        ComponentManager::terminate();
        SystemManager::terminate();
        ArchetypeManager::terminate();
    }

    void World::update(float delta)
    {
        SystemManager::getSingleton()->update(delta);
        cleanDestroyQueue();
    }

    void World::draw(Graphics& graphics)
    {
        SystemManager::getSingleton()->draw(graphics);
    }

    Entity World::create(std::shared_ptr<Archetype> archetype)
    {
        // create entity
        Entity createdEntity = entities.alloc();
        EntityData *data = entities.get(createdEntity);
        
        data->archetype = archetype.get();
        data->isDestroyed = false;
        
        //add entity to archetype
        archetype->addEntity(createdEntity);
        
        return createdEntity;
    };

    void World::destroy(Entity entity)
    {
        EntityData* data = entities.get(entity);
        if (data->isDestroyed)
            return;
        //queue entity to destroy
        data->isDestroyed = true;

        destroyQueue.push_back(entity);
    }
    
    void World::cleanDestroyQueue()
    {
        for (auto entity: destroyQueue)
        {
            EntityData *data = entities.get(entity);
            auto* archetype = data->archetype;
            archetype->removeEntity(entity);
        }
        destroyQueue.clear();
    }

} // namespace ASEngine
