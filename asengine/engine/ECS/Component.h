#ifndef ASENGINE_COMPONENT_H
#define ASENGINE_COMPONENT_H

#include <cstdint>
#include "engine/String/UniqueString.h"
#include "Entity.h" 

namespace ASEngine
{
    // base component type
    struct Component
    {

    };

    // component
    template <typename T>
    struct TComponent: Component
    {
        // basic constructor
        TComponent(){};

        // component name
        static UniqueString s_Name;

        // component signature
        static uint32_t s_Signature;
    };

    // component name implementation
    template <typename T>
    UniqueString TComponent<T>::s_Name = CHUNK_NULL;

    // component signature
    template <typename T>
    uint32_t TComponent<T>::s_Signature = 0;

}


#endif