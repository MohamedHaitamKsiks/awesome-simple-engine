#ifndef ASENGINE_MODULE_MANAGER_H
#define ASENGINE_MODULE_MANAGER_H

#include <memory>
#include <vector>

#include "Core/Singleton/Singleton.h"
#include "Module.h"

namespace ASEngine
{
    // module manager
    class ModuleManager: public Singleton<ModuleManager>
    {
    public:
        // register new module
        template <typename T>
        void RegisterModule()
        {
            static_assert(std::is_base_of_v<IModule, T>);

            std::unique_ptr<IModule> newModule = std::make_unique<T>();
            m_Modules.push_back(std::move(newModule));
        }

    
    protected:
        // only allow Application class to call these functions
        friend class Application;
        // call registry of every module
        void Registry();

    private:
        // registered modules
        std::vector<std::unique_ptr<IModule>> m_Modules{};
    };

} // namespace ASEngine

#endif // ASENGINE_MODULE_MANAGER_H