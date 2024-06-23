
#ifndef __ASENGINE_IMAGE_H
#define __ASENGINE_IMAGE_H

#include <cstdint>
#include <string>

// #include "Resource/Resource.h"
#include "Core/Memory/ByteBuffer.h"
#include "Renderer/Color.h"

#include "API/API.h"

namespace ASEngine 
{
    // image resource
    class ASENGINE_API Image
    {
    public:
        //constructor
        Image() = default;

        // create from with and height
        void Create(uint32_t width, uint32_t height);
        
        // load png
        void LoadPNG(const std::string& path);

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
