#ifndef ASENGINE_TRANSFORM_COMPONENT_H
#define ASENGINE_TRANSFORM_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds transoorm data
struct TransformComponent: Component<TransformComponent>
{
    Entity owner = 0;
    vec2 position = vec2{0.0f, 0.0f};
    vec2 velocity = vec2{0.0f, 0.0f};

    TransformComponent(){};

    TransformComponent(const vec2 &_position, const vec2 &_velocity)
    {
        position = _position;
        velocity = _velocity;
    };
};



#endif