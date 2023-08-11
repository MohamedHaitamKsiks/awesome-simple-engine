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

    // on render 2d
    void OnRender2D()
    {
        ForEach([](SpriteComponent &sprite, TransformComponent &transform)
        {
            mat3 spriteTransform = mat3::Transform(transform.Position, transform.Scale, transform.Rotation) * mat3::Translate(vec2::ONE() * -24.0f) ;
            Quad2D spriteQuad = Quad2D(sprite.Size, spriteTransform, Color::WHITE(), sprite.Frame, sprite.Frames, 0, 1);
            Renderer2D::DrawQuad(spriteQuad, sprite.MaterialID); 
        });
    }

    // on input
    void OnInputEvent(const InputEvent &event)
    {

        if (event.GetType() == InputEventType::MOUSE_BUTTON && event.Get<InputEventMouseButton>().Pressed)
        {
             Window::SetFullscreen(!Window::IsFullscreen());
        }

        if (event.GetType() == InputEventType::MOUSE_MOVE)
        {
            vec2 mousePosition = event.Get<InputEventMouseMove>().Position;
            mousePosition = mousePosition * Viewport::GetSize() / Window::GetSize() - Viewport::GetSize() * 0.5f;
            
            ForEach([&event, &mousePosition](SpriteComponent &sprite, TransformComponent &transform)
            { 
                transform.Position = mousePosition;
             });
        }
    }
};


#endif
