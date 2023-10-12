#include "ModuleManager.h"

namespace ASEngine
{
    ModuleManager::~ModuleManager()
    {
        // clean up modules
        for (auto* registeredModule: m_Modules)
        {
            delete registeredModule;
        }
    }

    void ModuleManager::RegisterComponents()
    {
        for (auto *registeredModule : GetSingleton()->m_Modules)
        {
            registeredModule->RegisterComponents();
        }
    }

    void ModuleManager::RegisterSystems()
    {
        for (auto *registeredModule : GetSingleton()->m_Modules)
        {
            registeredModule->RegisterSystems();
        }
    }

    void ModuleManager::InitResourceManagers()
    {
        for (auto *registeredModule : GetSingleton()->m_Modules)
        {
            registeredModule->InitResourceManagers();
        }
    }

    void ModuleManager::TerminateResourceManagers()
    {
        for (auto *registeredModule : GetSingleton()->m_Modules)
        {
            registeredModule->TerminateResourceManagers();
        }
    }

} // namespace ASEngine
