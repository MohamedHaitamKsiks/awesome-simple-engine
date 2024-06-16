#include "Texture.h"

namespace ASEngine
{
    void Texture::Create(const Image &image, TextureFilter filter, TextureRepeatMode repeat)
    {
        // save data
        m_Width = image.GetWidth();
        m_Height = image.GetHeight();
        m_Filter = filter;
        m_RepeatMode = repeat;

        // call implementation
        CreateImp(image, filter, repeat);
    }
} // namespace ASEngine
