#ifndef ASENGINE_SYSTEM_MANAGER_H
#define ASENGINE_SYSTEM_MANAGER_H

#include <memory>
#include <vector>
#include <map>
#include <functional>

#include "Core/InputSystem/InputEvent.h"
#include "Core/Singleton/Singleton.h"

#include "System.h"

namespace ASEngine
{
    class SystemManager: public Singleton<SystemManager>
    {
    public:
        // register system to the system manager
        template <typename SystemType>
        void RegisterSystem()
        {
            // check if T is a system
            static_assert(std::is_base_of_v<ISystem, SystemType>);

            // create new system
            std::unique_ptr<ISystem> system = std::make_unique<SystemType>();
            m_Systems.push_back(std::move(system));
        }

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

        // execute function for each system
        void ForEach(std::function<void(ISystem&)> callback, bool reversed = false);
    };

} // namespace ASEngine


#endif