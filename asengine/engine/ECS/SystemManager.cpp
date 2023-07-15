#include "SystemManager.h"

namespace ASEngine
{
    void SystemManager::registerArchetype(std::shared_ptr<Archetype> archetype)
    {
        uint32_t archetypeSignature = archetype->getSignature();

        for (auto system: systems)
        {
            uint32_t systemSignature = system->getSignature();
            //check if system signature is a part of archetype signature
            if (archetypeSignature % systemSignature == 0)
            {
                // add archetype to the system
                system->archetypes.push_back(archetype);
            }
            
        }
    }

    void SystemManager::update(float delta)
    {
        for (auto system: systems)
        {
            system->onUpdate(delta);
        }
    }

    void SystemManager::draw(Graphics& graphics)
    {
        for (auto system : systems)
        {
            system->onDraw(graphics);
        }
    }
} // namespace ASEngine
