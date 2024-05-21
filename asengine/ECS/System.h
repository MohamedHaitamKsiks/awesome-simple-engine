#ifndef ASENGINE_SYSTEM_H
#define ASENGINE_SYSTEM_H

#include "Core/InputSystem/InputEvent.h"

namespace ASEngine
{
    // system interface
    class ISystem
    {
    public:
        // init system
        virtual void Init() {};

        // on update (game logic)
        virtual void Update(float delta) {};

        // on fixed update (physics related logic)
        virtual void FixedUpdate(float delta) {};

        // rendering logic
        virtual void Render() {};

        // on input event
        virtual void OnInputEvent(const InputEvent& event) {};

        // terminate system
        virtual void Terminate() {};

    };
} // namespace ASEngine


#endif
