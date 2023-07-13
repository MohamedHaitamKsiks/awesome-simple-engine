#ifndef ASENGINE_WORLD_H
#define ASENGINE_WORLD_H

#include <memory>

#include "../Memory/PoolAllocator.h"
#include "../Renderer/Graphics.h"
#include "../Singleton/Singleton.h"

#include "Entity.h"
#include "EntityData.h"

#include "Component.h"
#include "ComponentManager.h"

#include "Archetype.h"
#include "ArchetypeManager.h"

#include "System.h"
#include "SystemManager.h"

namespace ASEngine
{
    class World: public Singleton<World>
    {
    public: 
        // contructor
        World();

        // destructor
        ~World();

        // create entity based on an archetype
        Entity createEntity(std::shared_ptr<Archetype> archetype);

        // destroy entity
        void destroyEntity(Entity entity);

        // update the world
        void update(float delta);

        // render the world
        void draw(Graphics &graphics);

    private:
        // entity managements
        PoolAllocator<EntityData> entities{UINT16_MAX};


    };

} // namespace ASENGINE

#endif