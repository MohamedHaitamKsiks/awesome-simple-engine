#ifndef ASENGINE_COMPONENT_H
#define ASENGINE_COMPONENT_H

#include <cstdint>
#include "engine/String/UniqueString.h"
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
        static UniqueString s_Name;

        // component signature
        static uint32_t s_Signature;
    };

    // component name implementation
    template <typename T>
    UniqueString Component<T>::s_Name = CHUNK_NULL;

    // component signature
    template <typename T>
    uint32_t Component<T>::s_Signature = 0;

}


#endif