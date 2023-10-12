#ifndef ASENGINE_MODULE_MANAGER_H
#define ASENGINE_MODULE_MANAGER_H

#include "Core/Singleton/Singleton.h"
#include "Core/Memory/DynamicArray.h"

#include "Module.h"

namespace ASEngine
{
    // module manager
    class ModuleManager: public Singleton<ModuleManager>
    {
    public:
        ~ModuleManager();

        // register new module
        template <typename T>
        static void RegisterModule()
        {
            static_assert(std::is_base_of_v<IModule, T>);

            IModule* newModule = new T();
            GetSingleton()->m_Modules.Push(newModule);
        }

        // call component registry for every module
        static void RegisterComponents();

        // call system registry for every module
        static void RegisterSystems();

        // init resource managers for every module
        static void InitResourceManagers();

        // terminate resource managers for every module
        static void TerminateResourceManagers();

    private:
        // registered modules
        TDynamicArray<IModule*> m_Modules{};
    };

} // namespace ASEngine

#endif // ASENGINE_MODULE_MANAGER_H