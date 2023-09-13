#include "SpriteRenderer2D.h"

void SpriteRenderer2D::OnCreate()
{
    // get sprite 
    SpriteID = ResourceManager<Sprite>::GetResourceId(SpriteName);
    const auto& sprite = ResourceManager<Sprite>::Get(SpriteID);

    // get sprite data
    MaterialID = sprite.GetDefaultMaterial();
    Size = vec2
    {
        (float) sprite.GetWidth(),
        (float) sprite.GetHeight()
    };
    Frames = sprite.GetFrames();
}

EXPORT(SpriteRenderer2D, SpriteName, FrameRate, Frame, Offset, Centered, Modulate)
