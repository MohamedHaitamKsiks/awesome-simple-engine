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

        ForEach([&delta](SpriteComponent& sprite, TransformComponent& transform)
        {
            sprite.Frame += sprite.FrameRate * delta;
            mat3 spriteTransform = mat3::Transform(transform.Position, transform.Scale, transform.Rotation);
            Quad2D spriteQuad = Quad2D(sprite.Size, spriteTransform, Color::WHITE(), sprite.Frame, sprite.Frames, 0, 1);
            Renderer2D::DrawQuad(spriteQuad, sprite.MatID);

        });

        Renderer2D::End();
    }

};


#endif
