#ifndef ASENGINE_COMPONENT_H
#define ASENGINE_COMPONENT_H

#include <cstdint>

#include "../String/UniqueString.h"
#include "Entity.h"

namespace ASEngine
{

    typedef uint32_t ComponentID;

    //abstract class for components
    class Component 
    {
    public:
        // contructor for entity
        Component(ComponentID _id, Entity _owner);
        // get id
        ComponentID getId() const;
        // get entity owenr
        Entity getOwner() const;
        // is component active
        bool isActive();
        // destroy componenet
        void destroy();
    private:
        // component index in the world
        ComponentID id;
        // component owner
        Entity owner;
        // active
        bool active = false;
    }

}


#endif