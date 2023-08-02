
#ifndef ASENGINE_IMAGE_H
#define ASENGINE_IMAGE_H

#include <cstdint>
#include <string>

#include "Resource.h"
#include "engine/FileSystem/File.h"
#include "engine/Log/Log.h"

namespace ASEngine {

    enum class ImageFormat 
    {
        RGBA,
        GRAYSCALE,
        GRAYSCALE_ALPHA
    };

    class Image : public Resource
    {

    public:
        //constructor
        Image() {};
        Image(uint8_t* pixels, int width, int height, ImageFormat format);

        ~Image();

        //load image
        bool Load(const std::string& imagePath);
    
        // get image pixels
        inline uint8_t* GetPixels() const { return m_Pixels; };

        // get image width
        inline int GetWidth() const { return m_Width; };

        // get image height
        inline int GetHeight() const { return m_Height; };

        // get image format 
        inline ImageFormat GetFormat() const { return m_Format; };

    private:
        // image format
        ImageFormat m_Format = ImageFormat::RGBA;

        // pixel buffer for the image
        uint8_t *m_Pixels = nullptr;

        int m_Width = -1;
        int m_Height = -1;
        
        int m_Channels = -1;

        // load method
        bool m_LoadedWithSTBI = false;
    };

} // ASEngine

#endif //ASENGINE_IMAGE_H
