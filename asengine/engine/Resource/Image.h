//
// Created by ksiks_wa3r on 3/18/23.
//

#ifndef MY_APPLICATION_IMAGE_H
#define MY_APPLICATION_IMAGE_H

#include <string>

#include "../Log/Log.h"
#include "Resource.h"

    namespace ASEngine {

    enum ImageFormat {
        IMAGE_FORMAT_RBGA,
        IMAGE_FORMAT_GRAYSCALE,
        IMAGE_FORMAT_GRAYSCALE_ALPHA,
        IMAGE_FORMAT_INTENSITY
    };

    typedef std::string ImageID;

    class Image: public Resource {

    public:
        char* pixels;
        int width;
        int height;
        ImageFormat format = IMAGE_FORMAT_RBGA;
        //constructor
        Image(char* _pixels, int _width, int _height);

        //load image
        static Image load(const std::string& imagePath);

        //add
        static void add(const ImageID& imageId, Image &image);

        //terminate
        static void terminate();

        //destroy
        void destroy();

        //equiv between ResourceID and Resource
        //= operator
        Image& operator=(const ImageID& imageId) {
            return Image::images[imageId];
        }

        //constructors
        Image() {};
        Image(const ImageID& imageId) {
            *this = Image::images[imageId];
        }

        static std::unordered_map<ResourceID, Image> images;
    };

} // ASEngine

#endif //MY_APPLICATION_IMAGE_H
