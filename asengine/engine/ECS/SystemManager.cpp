#include "SystemManager.h"

namespace ASEngine
{

    void SystemManager::ForEach(std::function<void(ISystem&)> callback, bool reversed)
    {
        if (reversed)
        {
            for (int i = m_Systems.size() - 1; i >= 0; i--)
            {
                callback(*m_Systems[i]);
            }
        }
        else
        {
            for (auto &system : m_Systems)
            {
                callback(*system);
            }
        }
    }

    void SystemManager::Init()
    {
        ForEach([](ISystem& system)
        { 
            system.Init(); 
        });
    }

    void SystemManager::Update(float delta)
    {
        ForEach([=](ISystem& system)
        {
            system.Update(delta);
        });
    }

    void SystemManager::FixedUpdate(float delta)
    {
        ForEach([=](ISystem& system)
        { 
            system.FixedUpdate(delta); 
        });
    }

    void SystemManager::OnInputEvent(const InputEvent &event)
    {
        ForEach([=](ISystem& system)
        {
            system.OnInputEvent(event); 
        });
    }

    void SystemManager::Terminate()
    {
        ForEach([](ISystem& system)
        {
            system.Terminate();
        }, true);
    }

} // namespace ASEngine
