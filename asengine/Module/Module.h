#ifndef __ASENGINE_MODULE_H
#define __ASENGINE_MODULE_H

#include "API/API.h"

namespace ASEngine
{
    // module
    class ASENGINE_API IModule
    {
    public:
        virtual ~IModule() {}

        virtual void Registry() = 0;
    };
    
} // namespace ASEngine

#endif // __ASENGINE_MODULE_H