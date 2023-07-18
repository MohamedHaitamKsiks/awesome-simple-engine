#ifndef ASENGINE_TRANSFORM_COMPONENT_H
#define ASENGINE_TRANSFORM_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds transoorm data
struct TransformComponent: Component<TransformComponent>
{
    vec2 Position = vec2{0.0f, 0.0f};
    vec2 Velocity = vec2{0.0f, 0.0f};
};



#endif