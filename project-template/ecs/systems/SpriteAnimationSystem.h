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

    // on input
    void OnInputEvent(const InputEvent &event)
    {
        if (event.GetType() == InputEventType::KEYBOARD && event.Get<InputEventKeyboard>().Code == GLFW_KEY_A && event.Get<InputEventKeyboard>().Pressed)
        {
            ForEach([&event](SpriteComponent &sprite)
            { 
                sprite.Frame = 0.0f;
             });
        }
    }
};

#endif
