#ifndef ASENGINE_SPRITE_COMPONENT_H
#define ASENGINE_SPRITE_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds sprite data
struct SpriteComponent : Component<SpriteComponent>
{
    ResourceID spriteId = 0;
    float frame = 0;
    float frameRate = 8.0f;

    SpriteComponent(){};

    SpriteComponent(ResourceID _spriteId)
    {
        spriteId = _spriteId;
    };
};



#endif