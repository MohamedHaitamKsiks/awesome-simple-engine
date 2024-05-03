#ifndef ASENGINE_SYSTEM_H
#define ASENGINE_SYSTEM_H

#include "Core/InputSystem/InputEvent.h"

namespace ASEngine
{
    // system interface
    class ISystem
    {
    public:
        // on create
        virtual void Init() {};

        // on update
        virtual void Update(float delta) {};

        // on fixed update
        virtual void FixedUpdate(float delta) {};

        // on input event
        virtual void OnInputEvent(const InputEvent& event) {};

        // terminate system
        virtual void Terminate() {};

    };
} // namespace ASEngine


#endif
