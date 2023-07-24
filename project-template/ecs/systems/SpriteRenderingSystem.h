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
        Renderer2D::Begin();

        ForEach([&delta](SpriteComponent *sprite, TransformComponent *transform)
        {
            vec2 size = vec2{(float) sprite->SpriteTexture.GetWidth(), (float) sprite->SpriteTexture.GetHeight()};
            mat3 spriteTransform = mat3::IDENTITY();
            Quad2D spriteQuad = Quad2D(size, spriteTransform, Color::WHITE());
            Renderer2D::DrawQuad(spriteQuad, sprite->MatID);
        });

        Renderer2D::End();
    }

};


#endif
