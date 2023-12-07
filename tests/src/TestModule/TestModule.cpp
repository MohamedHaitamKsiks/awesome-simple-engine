#include "TestModule.h"

void TestModule::RegisterComponents() 
{
    // register components
}

void TestModule::RegisterSystems()
{
    SystemManager::RegisterSystem<TestSystem>();
}

void TestModule::InitResourceManagers()
{
    // init resource managers
}

void TestModule::TerminateResourceManagers()
{
    // terminate resource managers
}
