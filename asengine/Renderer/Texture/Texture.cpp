#include "Texture.h"

namespace ASEngine
{
    void Texture::Create(const Image &image, TextureFormat format, TextureFilter filter, TextureRepeatMode repeat)
    {
        // call implementation
        CreateImp(image, format, filter, repeat);

        // save data
        m_Width = image.GetWidth();
        m_Height = image.GetHeight();
        m_Format = format;
        m_Filter = filter;
        m_RepeatMode = repeat;
    }
} // namespace ASEngine
