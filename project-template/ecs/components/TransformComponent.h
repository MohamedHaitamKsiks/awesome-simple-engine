#ifndef ASENGINE_TRANSFORM_COMPONENT_H
#define ASENGINE_TRANSFORM_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds transoorm data
struct TransformComponent: TComponent<TransformComponent>
{
    vec2 Position = vec2::ZERO();
    vec2 Scale = vec2::ONE();
    float Rotation = 0.0f;
};

template <>
Json Serializer<TransformComponent>::Serialize(const TransformComponent &value)
{
    Json object = Json({});
    return object;
}
template <>
void Serializer<TransformComponent>::Deserialize(const Json &object, TransformComponent &dest)
{
    assert(object.is_object());
}

#endif