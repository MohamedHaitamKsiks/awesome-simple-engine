#ifndef ASENGINE_SYSTEM_MANAGER_H
#define ASENGINE_SYSTEM_MANAGER_H

#include <memory>
#include <vector>

#include "Core/InputSystem/InputEvent.h"
#include "Core/Singleton/Singleton.h"

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
        
        // create all system
        static void inline Create() { GetSingleton()->ICreate(); }

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
       
        void ICreate();
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
        bool isSystemInserted = false;

        // insert new system and keep order
        std::vector<std::shared_ptr<BaseSystem>> newSystems{};

        for (int i = 0; i < m_Systems.size(); i++)
        {
            if (!isSystemInserted && m_Systems[i]->GetPriority() > system->GetPriority())
            {
                newSystems.push_back(system);
                isSystemInserted = true;
            }
            newSystems.push_back(m_Systems[i]);
        }
        
        if (!isSystemInserted)
            newSystems.push_back(system);

        // copy new systems
        m_Systems = newSystems;
    };
} // namespace ASEngine


#endif