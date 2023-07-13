#ifndef ASENGINE_COMPONENT_H
#define ASENGINE_COMPONENT_H

#include <cstdint>  
#include "../String/UniqueString.h"
#include "Entity.h" 

#define ComponentNameOf(componentType) (Component<componentType>::name)

namespace ASEngine
{

    // abstract class for components
    template <typename T>
    class Component 
    {
    public:
        // component owner
        Entity owner;

        // component name
        static UniqueString name;

        // component signature
        static uint32_t signature;
    };

    // component name implementation
    template <typename T>
    UniqueString Component<T>::name = UniqueString();

    // component signature
    template <typename T>
    uint32_t Component<T>::signature = 0;
}


#endif