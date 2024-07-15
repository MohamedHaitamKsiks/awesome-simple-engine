#ifndef __ASENGINE_INPUT_SYSTEM_H
#define __ASENGINE_INPUT_SYSTEM_H

#include "Core/Singleton/Singleton.h"

#include "ECS/System.h"
#include "API/API.h"

namespace ASEngine
{
    class ASENGINE_API InputSystem: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(InputSystem);
    public:
        
    private:
    };
} // namespace ASEngine

#endif // __ASENGINE_INPUT_SYSTEM_H