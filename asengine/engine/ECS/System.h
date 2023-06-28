#ifndef ASENGINE_ISYSTEM_H
#define ASENGINE_ISYSTEM_H

#include "Component.h"

namespace ASEngine
{
    // ecs system interface template 
    template<typename T>
    class ISystem 
    {
        // on create
        virtual void onCreate(T* data) = 0;
    
        // on update
        virtual void onUpdate(T* data, float delta) = 0;
    
    }
} // namespace ASEngine


#endif
