//
// Created by ksiks_wa3r on 3/18/23.
//

#ifndef MY_APPLICATION_IMAGE_H
#define MY_APPLICATION_IMAGE_H

#include <string>

#include "Resource.h"
#include "../FileSystem/File.h"
#include "../Log/Log.h"

namespace ASEngine {

    enum ImageFormat {
        IMAGE_FORMAT_RBGA,
        IMAGE_FORMAT_GRAYSCALE,
        IMAGE_FORMAT_GRAYSCALE_ALPHA,
        IMAGE_FORMAT_INTENSITY
    };

    class Image : public Resource {

    public:
        //pixel buffer for the image
        char* pixels = nullptr;
        //image width
        int width = -1;
        //image height
        int height = -1;
        //image format
        ImageFormat format = IMAGE_FORMAT_RBGA;
        
        //constructor
        Image() {};
        Image(char* _pixels, int _width, int _height);

        //destructor
        ~Image();

        //load image
        bool load(const std::string& imagePath);
    private:
        //image channels
        int channels = -1;

    };

} // ASEngine

#endif //MY_APPLICATION_IMAGE_H
