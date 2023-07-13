#ifndef ASENGINE_SPRITE_COMPONENT_H
#define ASENGINE_SPRITE_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds sprite data
struct SpriteComponent : public Component<SpriteComponent>
{
    ResourceID spriteId;
    float frame = 0;
    float frameRate = 8.0f;
};



#endif