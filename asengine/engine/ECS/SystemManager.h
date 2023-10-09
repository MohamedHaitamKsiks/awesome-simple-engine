#ifndef ASENGINE_SYSTEM_MANAGER_H
#define ASENGINE_SYSTEM_MANAGER_H

#include <memory>
#include <set>
#include <vector>

#include "Core/Memory/DynamicArray.h"
#include "Core/InputSystem/InputEvent.h"
#include "Core/Singleton/Singleton.h"

#include "System.h"

namespace ASEngine
{
    class SystemManager: public Singleton<SystemManager>
    {
    public:
        // destructor
        ~SystemManager();

        // register system to the system manager
        template <typename T>
        static void inline RegisterSystem() { GetSingleton()->IRegisterSystem<T>(); };

        // create all system
        static void inline Create() { GetSingleton()->ICreate(); }

        // update all system
        static void inline Update(float delta) { GetSingleton()->IUpdate(delta); };

        // render all system
        static void inline Render2D() { GetSingleton()->IRender2D(); };

        // render all system ui
        static void inline UIRender2D() { GetSingleton()->IUIRender2D(); };

        // process input for all system
        static void inline ProcessInputEvent(const InputEvent &event) { GetSingleton()->IProcessInputEvent(event); };

    private:
        TDynamicArray<ISystem*> m_Systems = {};

        template <typename T>
        void IRegisterSystem();
       
        void ICreate();
        void IUpdate(float delta);
        void IRender2D();
        void IUIRender2D();
        void IProcessInputEvent(const InputEvent& event);
    };

    // implementation of register system
    template <typename T>
    void SystemManager::IRegisterSystem()
    {
        // check if T is a system
        static_assert(std::is_base_of_v<ISystem, T>);

        // create new system
        ISystem* system = new T();
        bool isSystemInserted = false;

        // insert new system and keep order
        TDynamicArray<ISystem*> newSystems{};

        for (int i = 0; i < m_Systems.GetSize(); i++)
        {
            if (!isSystemInserted && m_Systems[i]->GetPriority() > system->GetPriority())
            {
                newSystems.Push(system);
                isSystemInserted = true;
            }
            newSystems.Push(m_Systems[i]);
        }
        
        if (!isSystemInserted)
            newSystems.Push(system);

        // copy new systems
        m_Systems = newSystems;

    };
} // namespace ASEngine


#endif