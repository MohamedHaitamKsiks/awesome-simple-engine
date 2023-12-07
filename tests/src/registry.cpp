#include "registry.h"
#include "TestModule/TestModule.h"

void Registry()
{
    ModuleManager::RegisterModule<TestModule>();
}