#include "SystemManager.h"

namespace ASEngine
{
    void SystemManager::IRegisterArchetype(std::shared_ptr<Archetype> archetype)
    {
        const auto& archetypeSignature = archetype->GetSignature();

        for (auto system: m_Systems)
        {
            const auto& systemSignature = system->GetSignature();
            //check if system signature is a part of archetype signature
            if (std::includes(archetypeSignature.begin(), archetypeSignature.end(), systemSignature.begin(), systemSignature.end()) )
            {
                // add archetype to the system
                system->AddArchetype(archetype);
            }
            
        }
    }

    void SystemManager::ICreate()
    {
        for (auto system : m_Systems)
        {
            system->OnCreate();
        }
    }

    void SystemManager::IUpdate(float delta)
    {
        for (auto system : m_Systems)
        {
            system->OnUpdate(delta);
        }
    }

    void SystemManager::IRender2D()
    {
        for (auto system : m_Systems)
        {
            system->OnRender2D();
        }
    }

    void SystemManager::IProcessInputEvent(const InputEvent &event)
    {
        for (auto system : m_Systems)
        {
            system->OnInputEvent(event);
        }
    }

} // namespace ASEngine
