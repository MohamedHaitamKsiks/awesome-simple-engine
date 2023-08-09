#ifndef ASENGINE_TRANSFORM_COMPONENT_H
#define ASENGINE_TRANSFORM_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds transoorm data
struct TransformComponent: Component<TransformComponent>
{
    vec2 Position = vec2::ZERO();
    vec2 Scale = vec2::ONE();
    float Rotation = 0.0f;
};



#endif