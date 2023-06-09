//
// Created by ksiks_wa3r on 3/18/23.
//

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Thirdparty/stb_image.h"

namespace ASEngine {
    Image::Image(char* _pixels, int _width, int _height) {
        pixels = _pixels;
        width = _width;
        height = _height;
    }

    Image Image::load(const std::string& imagePath) {
		size_t fileLength;
        stbi_uc* buffer = (stbi_uc*) Resource::loadAsBinary(imagePath, &fileLength);

        //decode
        int width = -1, height = -1, channels = -1;
        
        
        char* pixels =  (char*) stbi_load_from_memory(buffer, (int) fileLength, &width, &height, &channels, STBI_rgb_alpha);
        if (!pixels) {
            auto *StbError = stbi_failure_reason();
            if (!StbError)
                StbError = "Unknown error";
            std::stringstream Error;
            Error << "Failed to read image pixels; " << StbError;

            Log::out(Error.str());
        }


        //create image resource
        Image image{pixels, width, height};
		image.format = IMAGE_FORMAT_RBGA;

        //add image to resources
        ImageID imageId = Resource::generateId();
        Image::add(imageId, image);

        std::stringstream ss;
        ss << "Image created " << image.width << "x" << image.height << "\n"; 
        Log::out(ss.str());

        delete buffer;

        return image;
    }

    void Image::add(const ImageID& imageId, Image &image) {
        image.id = imageId;
        Image::images[imageId] = image;
    }

    void Image::destroy() {
        delete pixels;
        //Image::images.erase(id);
    }

    std::unordered_map<ResourceID, Image> Image::images = {};

    void Image::terminate() {
        images.clear();
    }


} // ASEngine