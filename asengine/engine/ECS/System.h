#ifndef ASENGINE_SYSTEM_H
#define ASENGINE_SYSTEM_H

#include <memory>
#include <functional>
#include <set>
#include <vector>
#include <tuple>

#include "Core/InputSystem/InputEvent.h"
#include "Core/Memory/DynamicArray.h"

#include "Archetype.h"
#include "Component.h"
#include "ComponentManager.h"
#include "Signature.h"

namespace ASEngine
{
    // system interface
    class ISystem
    {
    public:

        // get priority
        inline int GetPriority() const
        {
            return m_Priority;
        };

        // on create
        virtual void OnCreate() {};

        // on update
        virtual void OnUpdate(float delta) {};

        // on fixed update
        virtual void OnFixedUpdate(float delta) {};

        // on render
        virtual void OnRender2D() {};

        // on render ui
        virtual void OnUIRender2D() {};

        // on input event
        virtual void OnInputEvent(const InputEvent& event) {};

    private:
        // system priority
        int m_Priority = 0;

        // archetypes list
        TDynamicArray<Archetype*> m_Archetypes{};
    };
} // namespace ASEngine


#endif
