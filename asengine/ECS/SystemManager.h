#ifndef __ASENGINE_SYSTEM_MANAGER_H
#define __ASENGINE_SYSTEM_MANAGER_H

#include <memory>
#include <vector>
#include <map>
#include <functional>

#include "Core/InputSystem/InputEvent.h"
#include "Core/Singleton/Singleton.h"

#include "System.h"



// register system class
#define ASENGINE_REGISTER_SYSTEM(systemClass) SystemManager::GetInstance().RegisterSystem<systemClass>()

namespace ASEngine
{
    class  SystemManager
    {
    ASENGINE_DEFINE_SINGLETON(SystemManager);
    public:
        ~SystemManager();

        // register system to the system manager
        template <typename SystemType>
        void RegisterSystem()
        {
            // check if T is a system
            static_assert(std::is_base_of_v<ISystem, SystemType>);

            // create new system
            std::unique_ptr<ISystem> system = std::make_unique<SystemType>();
            RegisterSystem(std::move(system));
        }

        // register system
        void RegisterSystem(std::unique_ptr<ISystem> system);

        // create all system
        void Init();

        // update all system
        void Update(float delta);

        // fixed update systems
        void FixedUpdate(float delta);

        // process input for all system
        void OnInputEvent(const InputEvent &event);

        // terminate system
        void Terminate();

    private:
        std::vector<std::unique_ptr<ISystem>> m_Systems = {};
    };
} // namespace ASEngine


#endif