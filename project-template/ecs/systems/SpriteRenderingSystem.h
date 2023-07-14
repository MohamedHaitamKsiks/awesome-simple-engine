#ifndef ASENGINE_SPRITE_RENDERING_SYSTEM_H
#define ASENGINE_SPRITE_RENDERING_SYSTEM_H

#include "../components/SpriteComponent.h"
#include "../components/TransformComponent.h"

#include "engine/asengine.h"

using namespace ASEngine;

// render sprites on screen
class SpriteRenderingSystem: public System<SpriteComponent, TransformComponent>
{
public:
    // on update
    void onUpdate(float delta)
    {
        forEach([&delta](SpriteComponent *sprite, TransformComponent *transform)
        {
            sprite->frame += delta * sprite->frameRate;
        });
    }

    // on draw
    void onDraw(Graphics &graphics)
    {
        forEach([&graphics](SpriteComponent *sprite, TransformComponent *transform)
        {
            Sprite* spriteResource = ResourceManager<Sprite>::getSingleton()->get(sprite->spriteId);
            graphics.drawSprite(spriteResource, sprite->frame, transform->position);
        });
    }
};


#endif
