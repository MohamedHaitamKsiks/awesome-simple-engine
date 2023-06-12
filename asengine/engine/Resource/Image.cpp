//
// Created by ksiks_wa3r on 3/18/23.
//

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Thirdparty/stb_image.h"

namespace ASEngine {

    Image::Image(char* _pixels, int _width, int _height) 
    {
        pixels = _pixels;
        width = _width;
        height = _height;
    }

    bool Image::load(const std::string& imagePath) 
    {
        //read image file
        File imageFile;
        if(!imageFile.open(imagePath, FILE_OPEN_MODE_READ)) 
        {
            std::stringstream error;
            error << "Cannot open image: " << imagePath;
            Log::out(error.str());
            return false;
        }
        size_t fileLength = imageFile.getSize();
        stbi_uc buffer[fileLength];
        imageFile.read((char*) buffer);

        //decode
        pixels =  (char*) stbi_load_from_memory(buffer, (int) fileLength, &width, &height, &channels, STBI_rgb_alpha);
        if (!pixels) 
        {
            auto *StbError = stbi_failure_reason();
            if (!StbError)
                StbError = "Unknown error";
            std::stringstream error;
            error << "Failed to read image pixels; " << StbError;

            Log::out(error.str());
            return false;
        }


        //create image resource
		format = IMAGE_FORMAT_RBGA;

        //log image created
        std::stringstream ss;
        ss << "Image created " << width << "x" << height << "\n"; 
        Log::out(ss.str());
        
        imageFile.close();
        return true;
    }

    Image::~Image() 
    {
        if (pixels)
            delete pixels;
    }

} // ASEngine