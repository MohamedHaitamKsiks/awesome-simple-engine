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

    Image Image::load(const std::string& imagePath) {
        //open asset
        AAsset* asset = AAssetManager_open(assetManager, imagePath.c_str(), AASSET_MODE_BUFFER);

        // Get the length of the file using AAsset_getLength.
        off_t fileLength = AAsset_getLength(asset);

        // Read the contents of the file using AAsset_read.
        stbi_uc* buffer = new stbi_uc[fileLength];
        int bytesRead = AAsset_read(asset, buffer, fileLength);

        //decode
        int width, height, channel;
        stbi_uc * pixels = stbi_load_from_memory(buffer, fileLength, &width, &height, &channel, STBI_rgb_alpha);

        //create image resource
        Image image{pixels, width, height};
		image.format = IMAGE_FORMAT_RBGA;

        //add image to resources
        ImageID imageId = Resource::generateId();
        Image::add(imageId, image);

        Log::out("Image created");

        //free buffer
        AAsset_close(asset);
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