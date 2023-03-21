//
// Created by ksiks_wa3r on 3/18/23.
//

#include "Image.h"

namespace ASEngine {
    Image::Image(stbi_uc* _pixels, int _width, int _height) {
        pixels = _pixels;
        width = _width;
        height = _height;
    }

    Image Image::load(std::string imagePath) {
        //open asset
        AAsset* asset = AAssetManager_open(assetManager, imagePath.c_str(), AASSET_MODE_BUFFER);

        // Get the length of the file using AAsset_getLength.
        off_t fileLength = AAsset_getLength(asset);

        // Read the contents of the file using AAsset_read.
        stbi_uc* buffer = new  stbi_uc[fileLength];
        int bytesRead = AAsset_read(asset, buffer, fileLength);

        //decode
        int width, height, channel;
        stbi_uc * pixels = stbi_load_from_memory(buffer, fileLength, &width, &height, &channel, STBI_rgb_alpha);

        //create image resource
        Image image{pixels, width, height};

        //add image to resources
        ImageID imageId = Resource::generateId();
        Image::add(imageId, image);

        //free buffer
        AAsset_close(asset);
        free(buffer);

        return image;
    }

    void Image::add(ImageID imageId, Image &image) {
        image.id = imageId;
        Image::images[imageId] = image;
    }

    void Image::destroy() {
        free(pixels);
        Image::images.erase(id);
    }

    std::unordered_map<ResourceID, Image> Image::images = {};


} // ASEngine