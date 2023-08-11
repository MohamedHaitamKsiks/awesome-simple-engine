#ifndef ASENGINE_SYSTEM_MANAGER_H
#define ASENGINE_SYSTEM_MANAGER_H

#include <memory>
#include <vector>

#include "engine/InputSystem/InputEvent.h"
#include "engine/Singleton/Singleton.h"

#include "System.h"

namespace ASEngine
{
    class SystemManager: public Singleton<SystemManager>
    {
    public:
        // register system to the system manager
        template <typename T>
        static void inline RegisterSystem() { GetSingleton()->IRegisterSystem<T>(); };
        // register archetype to system manager
        static void inline  RegisterArchetype(std::shared_ptr<Archetype> archetype) { GetSingleton()->IRegisterArchetype(archetype);};
        
        // update all system
        static void inline Update(float delta) { GetSingleton()->IUpdate(delta); };

        // render all system
        static void inline Render2D() { GetSingleton()->IRender2D(); };

        // process input for all system
        static void inline ProcessInputEvent(const InputEvent &event) { GetSingleton()->IProcessInputEvent(event); };

    private:
        std::vector<std::shared_ptr<BaseSystem>> m_Systems = {};

        template <typename T>
        void IRegisterSystem();
        void IRegisterArchetype(std::shared_ptr<Archetype> archetype);
       
        void IUpdate(float delta);
        void IRender2D();
        void IProcessInputEvent(const InputEvent& event);
    };

    // implementation of register system
    template <typename T>
    void SystemManager::IRegisterSystem()
    {
        // check if T is a system
        static_assert(std::is_base_of_v<BaseSystem, T>);

        // create new system
        std::shared_ptr<BaseSystem> system = std::make_shared<T>();
        m_Systems.push_back(system);
    };
} // namespace ASEngine


#endif