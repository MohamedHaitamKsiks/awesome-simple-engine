#ifndef ASENGINE_SPRITE_ANIMATION_SYSTEM_H
#define ASENGINE_SPRITE_ANIMATION_SYSTEM_H

#include "../components/SpriteComponent.h"

#include "engine/asengine.h"

using namespace ASEngine;

// animate sprite
class SpriteAnimationSystem : public System<SpriteComponent>
{
public:
    // on update
    void OnUpdate(float delta)
    {
        ForEach([&delta](SpriteComponent &sprite)
        { 
            sprite.Frame += sprite.FrameRate * delta; 
        });
    }

};

#endif
