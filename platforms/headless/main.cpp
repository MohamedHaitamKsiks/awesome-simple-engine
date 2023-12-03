#define ASENGINE_HEADLESS

#include "ASEngine.h"

using namespace ASEngine;

int main()
{
    Application::Create(Platform::DESKTOP);

    // init resource managers
    Application::InitResourceManagers();

    // load project settings
    Application::LoadProjectSettings();

    // module registry
    Registry();

    // init modules
    ModuleManager::InitResourceManagers();
    ModuleManager::RegisterComponents();
    ModuleManager::RegisterSystems();



    return 0;
}