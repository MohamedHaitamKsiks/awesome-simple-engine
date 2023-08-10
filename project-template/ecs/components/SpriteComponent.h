#ifndef ASENGINE_SPRITE_COMPONENT_H
#define ASENGINE_SPRITE_COMPONENT_H

#include "engine/asengine.h"

using namespace ASEngine;

// holds sprite data
struct SpriteComponent : TComponent<SpriteComponent>
{
    UniqueString SpritePath;
    ResourceID MaterialID = UINT32_MAX;
    ResourceID SpriteID = UINT32_MAX;
    vec2 Size = vec2::ZERO();
    float Frames = 1.0f;
    float Frame = 0.0f;
    float FrameRate = 8.0f;

    void OnCreate()
    {
        SpriteID = ResourceManager<Sprite>::GetResourceId(SpritePath);

        Sprite &sprite = ResourceManager<Sprite>::Get(SpriteID);

        MaterialID = sprite.GetDefaultMaterial();
        Frames = sprite.GetFrames();
        Size = vec2{(float)sprite.GetWidth(), (float)sprite.GetHeight()};
    }
};

EXPORT(SpriteComponent, SpritePath, Frame);

#endif