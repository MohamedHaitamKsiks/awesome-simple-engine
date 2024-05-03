#include "ASEngine.h"
#include "TestSystem/TestSystem.h"

namespace ASEngine
{
    void Registry()
    {
        SystemManager::GetInstance().RegisterSystem<TestSystem>();
    }
    
} // namespace ASEngine
