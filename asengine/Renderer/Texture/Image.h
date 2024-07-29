
#ifndef __ASENGINE_IMAGE_H
#define __ASENGINE_IMAGE_H

#include <cstdint>
#include <string>

// #include "Resource/Resource.h"
#include "Core/Memory/ByteBuffer.h"
#include "Renderer/Color.h"



namespace ASEngine
{
    // image resource
    class  Image
    {
    public:
        //constructor
        Image() = default;

        // create from with and height
        void Create(uint32_t width, uint32_t height);

        // load png
        void LoadPNG(const std::string& path);

        // get image pixel
        Color GetPixelAt(uint32_t x, uint32_t y) const;

        // set image pixel
        void SetPixelAt(uint32_t x, uint32_t y, const Color& color);

        // set image pixel with rgba as bytes
        void SetPixelAt(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        // get image width
        inline int GetWidth() const
        {
            return m_Width;
        }

        // get image height
        inline int GetHeight() const
        {
            return m_Height;
        }

        // get pixel buffer
        inline const ByteBuffer& GetPixels() const
        {
            return m_Pixels;
        }

    private:
        // pixel buffer for the image
        ByteBuffer m_Pixels{};

        int m_Width = -1;
        int m_Height = -1;

        int m_Channels = -1;
    };

} // ASEngine

#endif //ASENGINE_IMAGE_H
