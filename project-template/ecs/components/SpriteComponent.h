#ifndef ASENGINE_SPRITE_COMPONENT_H
#define ASENGINE_SPRITE_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds sprite data
struct SpriteComponent : TComponent<SpriteComponent>
{
    ResourceID MaterialID = UINT32_MAX;
    ResourceID SpriteID = UINT32_MAX;
    vec2 Size = vec2::ZERO();
    float Frames = 1.0f;
    float Frame = 0.0f;
    float FrameRate = 8.0f;
};

template <>
Json Serializer<SpriteComponent>::Serialize(const SpriteComponent &value)
{
    Json object = Json({});
    return object;
}
template <>
void Serializer<SpriteComponent>::Deserialize(const Json &object, SpriteComponent &dest)
{
    assert(object.is_object());
}

#endif