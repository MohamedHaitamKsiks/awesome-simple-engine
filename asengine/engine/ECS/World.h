#ifndef ASENGINE_WORLD_H
#define ASENGINE_WORLD_H

#include <memory>
#include <vector>

#include "engine/Memory/PoolAllocator.h"
#include "engine/Renderer/Graphics.h"
#include "engine/Singleton/Singleton.h"

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

        // destructorE
        ~World();

        // create entity based on an archetype
        Entity create(std::shared_ptr<Archetype> archetype);

        // create entity based on components signature
        template<typename T, typename... types>
        Entity create()
        {
            // get archetype
            std::shared_ptr<Archetype> archetype = ArchetypeManager::getSingleton()->getArchetype<T, types...>();
            // create entity
            return create(archetype);
        };

        // create entities with components values
        template <typename T, typename... types>
        Entity create(T firstComponent, types... components)
        {
            Entity entity = create<T, types...>();
            setComponents<T, types...>(entity, firstComponent, components...);
            return entity;
        };

        // set comonents of entity
        template <typename T, typename... types>
        void setComponents(Entity entity, const T& firstComponent, const types&... components)
        {
            // set first component
            T* component = getComponent<T>(entity);
            *component = firstComponent;

            if constexpr(sizeof...(components) > 0)
            {
                setComponents(entity, components...);
            }
            
        };

        // get component of entity
        template<typename T>
        T* getComponent(Entity entity)
        {
            // check if component is of component type
            static_assert(std::is_base_of_v<Component<T>, T>);

            // get component
            auto* archetype = entities.get(entity)->archetype;
            return archetype->getComponentOfEntity<T>(entity);
        };

        // destroy entity
        void destroy(Entity entity);

        // update the world
        void update(float delta);

        // render the world
        void draw(Graphics &graphics);

    private:
        // clear destroy queue executed at the end of the frame to delete
        void cleanDestroyQueue();
    
        // entity managements
        PoolAllocator<EntityData> entities{UINT16_MAX};
        
        // destroy queue
        std::vector<Entity> destroyQueue = {};


    };

} // namespace ASENGINE

#endif