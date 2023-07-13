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
        
    }

    // on draw
    void onDraw(Graphics &graphics)
    {
        UniqueString text = UniqueString("Ksiks Wa3r");

        ResourceID fontId = ResourceManager<Font>::getSingleton()->getResourceId(UniqueString("ft_default"));
        Font* font = ResourceManager<Font>::getSingleton()->get(fontId);
        graphics.drawText(text.getString(), vec2{32.0f, 32.0f}, font);


        ResourceID spriteId = ResourceManager<Sprite>::getSingleton()->getResourceId(UniqueString("spr_run"));
        Sprite* sprite = ResourceManager<Sprite>::getSingleton()->get(spriteId);
        graphics.drawSprite(sprite, 0, Screen::getCenter());
    }
};


#endif
