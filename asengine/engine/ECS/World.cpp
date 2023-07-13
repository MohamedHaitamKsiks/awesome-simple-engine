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
    }

    void World::draw(Graphics& graphics)
    {
        SystemManager::getSingleton()->draw(graphics);
    }

} // namespace ASEngine
