#include "SystemManager.h"

namespace ASEngine
{
    ;

    SystemManager::~SystemManager()
    {
    }

    void SystemManager::RegisterSystem(std::unique_ptr<ISystem> system)
    {
        m_Systems.push_back(std::move(system));
    }

    void SystemManager::Init()
    {
        for (auto& system: m_Systems)
        {
            system->Init(); 
        }
    }

    void SystemManager::Update(float delta)
    {
        for (auto &system : m_Systems)
        {
            system->Update(delta);
        }
    }

    void SystemManager::FixedUpdate(float delta)
    {
        for (auto &system : m_Systems)
        {
            system->FixedUpdate(delta);
        }
    }

    void SystemManager::OnInputEvent(const InputEvent &event)
    {
        for (auto &system : m_Systems)
        {
            system->OnInputEvent(event);
        }
    }

    void SystemManager::Terminate()
    {
        // terminate in the inverse orderer of init
        while (m_Systems.size() > 0)
        {
            auto& system = m_Systems.back();
            system->Terminate();
            
            m_Systems.pop_back();
        }
    }

} // namespace ASEngine
