//
// Created by ksiks_wa3r on 3/18/23.
//

#ifndef MY_APPLICATION_IMAGE_H
#define MY_APPLICATION_IMAGE_H

#include <string>
#include <android/asset_manager.h>

#include "../Thirdparty/stb_image.h"
#include "Resource.h"

namespace ASEngine {

    typedef std::string ImageID;

    class Image: Resource {
    public:
        stbi_uc * pixels;
        int width;
        int height;
        //constructor
        Image(stbi_uc* _pixels, int _width, int _height);

        //load image
        static Image load(std::string imagePath);

        //add
        static void add(ImageID imageId, Image &image);

        //destroy
        void destroy();

        //equiv between ResourceID and Resource
        //= operator
        Image& operator=(ImageID imageId) {
            return Image::images[imageId];
        }

        //constructors
        Image() {};
        Image(ImageID imageId) {
            *this = Image::images[imageId];
        }

        static std::unordered_map<ResourceID, Image> images;
    };

} // ASEngine

#endif //MY_APPLICATION_IMAGE_H
