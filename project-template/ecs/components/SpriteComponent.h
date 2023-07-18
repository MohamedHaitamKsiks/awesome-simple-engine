#ifndef ASENGINE_SPRITE_COMPONENT_H
#define ASENGINE_SPRITE_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds sprite data
struct SpriteComponent : Component<SpriteComponent>
{
    ResourceID SpriteId = 0;
    float Frame = 0;
    float FrameRate = 8.0f;

};



#endif