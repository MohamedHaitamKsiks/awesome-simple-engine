#include "Sprite.h"

namespace ASEngine 
{

    bool Sprite::Load(Texture texture, int frames, const vec2& offset) 
    {
        if (frames <= 0) 
            return false;

        m_Texture = texture;
        m_Width = texture.GetWidth() / frames;
        m_Height = texture.GetHeight();
        m_Frames = frames;
        m_Offset = offset;
        return true;
    }

} // ASEngine