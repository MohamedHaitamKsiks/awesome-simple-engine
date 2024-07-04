#include "ModuleManager.h"

namespace ASEngine
{
    void ModuleManager::Registry()
    {
        for (auto& module: m_Modules)
        {
            module->Registry();
        }
    }

} // namespace ASEngine
