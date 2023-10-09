#include "SystemManager.h"

namespace ASEngine
{
    SystemManager::~SystemManager()
    {
        for (auto system: m_Systems)
        {
            delete system;
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

    void SystemManager::IFixedUpdate(float delta)
    {
        for (auto system : m_Systems)
        {
            system->OnFixedUpdate(delta);
        }
    }

    void SystemManager::IRender2D()
    {
        for (auto system : m_Systems)
        {
            system->OnRender2D();
        }
    }

    void SystemManager::IUIRender2D()
    {
        for (auto system : m_Systems)
        {
            system->OnUIRender2D();
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
