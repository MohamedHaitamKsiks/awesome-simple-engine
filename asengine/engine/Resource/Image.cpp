#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Thirdparty/stb_image.h"

namespace ASEngine {

    Image::Image(uint8_t* pixels, int width, int height, ImageFormat format)
    {
        m_Pixels = pixels;
        m_Width = width;
        m_Height = height;
        m_Format = format;
    }

    Image::~Image()
    {
        if (!IsOwner())
            return;

        if (!m_Pixels) return;

        if (m_LoadedWithSTBI)
            stbi_image_free(m_Pixels);
        else
            delete[] m_Pixels;

        m_Pixels = nullptr;
    }

    bool Image::Load(const std::string& imagePath) 
    {
        //read image file
        File imageFile;
        if(!imageFile.Open(imagePath, FileOpenMode::READ)) 
        {
            Debug::Log("Cannot open image:", imagePath);
            return false;
        }

        size_t fileLength = imageFile.GetSize();
        stbi_uc buffer[fileLength];
        imageFile.Read((char*) buffer);

        //decode
        m_Pixels =  (uint8_t*) stbi_load_from_memory(buffer, (int) fileLength, &m_Width, &m_Height, &m_Channels, STBI_rgb_alpha);
        if (!m_Pixels) 
        {
            auto *stbError = stbi_failure_reason();
            if (!stbError)
                stbError = "Unknown error";
        
            Debug::Log("Failed to read image pixels:", stbError);
            return false;
        }

        m_LoadedWithSTBI = true;

        // create image resource
        m_Format = ImageFormat::RGBA;
        
        imageFile.Close();
        return true;
    }


} // ASEngine