#include "ASEngine.h"
#include "ASEngineTestSystem/ASEngineTestSystem.h"

namespace ASEngine
{
    void Registry()
    {
        SystemManager::GetInstance().RegisterSystem<ASEngineTestSystem>();
    }
    
} // namespace ASEngine
