#ifndef ASENGINE_SPRITE_COMPONENT_H
#define ASENGINE_SPRITE_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds sprite data
struct SpriteComponent : Component<SpriteComponent>
{
    ResourceID MaterialID = CHUNK_NULL;
    ResourceID SpriteID = CHUNK_NULL;
    vec2 Size = vec2::ZERO();
    float Frames = 1.0f;
    float Frame = 0.0f;
    float FrameRate = 8.0f;
};



#endif