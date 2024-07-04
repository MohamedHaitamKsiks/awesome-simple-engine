#ifndef __ASENGINE_SYSTEM_H
#define __ASENGINE_SYSTEM_H

#include "Core/InputSystem/InputEvent.h"
#include "API/API.h"

namespace ASEngine
{
    // system interface
    class ASENGINE_API ISystem
    {
    public:
        virtual ~ISystem() = default;

        // init system
        virtual void Init() {};

        // on update (game logic)
        virtual void Update(float delta) {};

        // on fixed update (physics related logic)
        virtual void FixedUpdate(float delta) {};

        // on input event
        virtual void OnInputEvent(const InputEvent& event) {};

        // terminate system
        virtual void Terminate() {};

    };
} // namespace ASEngine


#endif
