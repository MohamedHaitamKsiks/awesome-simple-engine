#ifndef ASENGINE_TRANSFORM_COMPONENT_H
#define ASENGINE_TRANSFORM_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds transoorm data
struct TransformComponent: public Component<TransformComponent>
{
    mat3 transform;
};



#endif