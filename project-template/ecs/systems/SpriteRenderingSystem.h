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
    void OnUpdate(float delta)
    {
        ForEach([&delta](SpriteComponent *sprite, TransformComponent *transform)
        {
            Debug::Log("render sprite", sprite->SpriteId);
        });
    }

};


#endif
