#ifndef ASENGINE_COMPONENT_H
#define ASENGINE_COMPONENT_H

#include <cstdint>  
#include "../String/UniqueString.h"
#include "Entity.h" 

namespace ASEngine
{

    // abstract class for components
    template <typename T>
    struct Component
    {
        // basic constructor
        Component() {};

        // component name
        static UniqueString name;

        // component signature
        static uint32_t signature;
    };

    // component name implementation
    template <typename T>
    UniqueString Component<T>::name = CHUNK_NULL;

    // component signature
    template <typename T>
    uint32_t Component<T>::signature = 0;

}


#endif