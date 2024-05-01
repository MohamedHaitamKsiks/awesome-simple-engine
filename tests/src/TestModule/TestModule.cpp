#include "TestModule.h"
#include "TestSystem.h"

void TestModule::Registry() 
{
    SystemManager::GetInstance().RegisterSystem<TestSystem>();
}

