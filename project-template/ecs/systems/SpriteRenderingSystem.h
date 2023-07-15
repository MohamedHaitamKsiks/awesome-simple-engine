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
            transform->position = transform->position + transform->velocity * delta;
           
            if (transform->position.x > Screen::getSize().x)
            {
                transform->position.x = Screen::getSize().x;
                transform->velocity.x *= -1.0f;
            }

            if (transform->position.x < 0.0f )
            {
                transform->position.x = 0.0f;
                transform->velocity.x *= -1.0f;
            }

            if (transform->position.y < 0.0f || transform->position.y > Screen::getSize().y * 0.5f)
            {
                World::getSingleton()->destroy(transform->owner);
            }
        });
    }

    // on draw
    void onDraw(Graphics &graphics)
    {
        forEach([&graphics](SpriteComponent *sprite, TransformComponent *transform)
        {
            Sprite* spriteResource = ResourceManager<Sprite>::getSingleton()->get(sprite->spriteId);
            graphics.drawSprite(spriteResource, sprite->frame, transform->position, Color::white);
        });
    }
};


#endif
