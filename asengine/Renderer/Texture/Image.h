
#ifndef ASENGINE_IMAGE_H
#define ASENGINE_IMAGE_H

#include <cstdint>
#include <string>

#include "Core/Memory/ByteBuffer.h"
#include "Renderer/Color.h"

namespace ASEngine 
{

    enum class ImageFormat 
    {
        RGBA,
        GRAYSCALE,
        GRAYSCALE_ALPHA
    };

    class Image
    {
    public:
        //constructor
        Image() = default;
        Image(int width, int height);

        //create image from .png path
        Image(const std::string& path);
    
        // get image pixel
        Color GetPixelAt(int x, int y) const;

        // set image pixel 
        void SetPixelAt(int x, int y, const Color& color);

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
