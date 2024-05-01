#include "ASEngine.h"
#include "TestModule/TestModule.h"

namespace ASEngine
{
    void Registry()
    {
        ModuleManager::GetInstance().RegisterModule<TestModule>();
    }
    
} // namespace ASEngine
