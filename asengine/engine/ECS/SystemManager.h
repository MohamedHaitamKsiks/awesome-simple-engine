#ifndef ASENGINE_SYSTEM_MANAGER_H
#define ASENGINE_SYSTEM_MANAGER_H

#include <memory>
#include <vector>

#include "engine/Renderer/Graphics.h"
#include "engine/Singleton/Singleton.h"

#include "System.h"

namespace ASEngine
{
    class SystemManager: public Singleton<SystemManager>
    {
    public:
        // register system to the system manager
        template <typename T>
        void registerSystem()
        {
            // check if T is a system
            static_assert(std::is_base_of_v<BaseSystem, T>);

            //create new system
            std::shared_ptr<BaseSystem> newSystem = std::make_shared<T>();
            systems.push_back(newSystem);
        };

        // register archetype to system manager
        void registerArchetype(std::shared_ptr<Archetype> archetype);

        // update all system
        void update(float delta);

        // draw all system
        void draw(Graphics& graphics);
    private:
        // list of registered systems
        std::vector<std::shared_ptr<BaseSystem>> systems = {};
    };
} // namespace ASEngine


#endif