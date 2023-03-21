//
// Created by ksiks_wa3r on 3/18/23.
//
#include "Texture.h"

namespace ASEngine {
    //init
    void Texture::init() {

    };

    //load texture from
    Texture Texture::load(Image& image) {
        //create GL texture
        GLuint texture;
        //load open gl texture
        glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.pixels);
        //create texture info
        TextureInfo info{texture, image.width, image.height};
        Texture::infoList.push_back(info);
        //return texture
        Texture loadedTexture{Texture::textureCounter++};
        return loadedTexture;
    }
    //destroy
    void Texture::destroy() {
        Texture::infoList.erase(Texture::infoList.begin() + id);
    }
    //get width
    int Texture::width() {
        return Texture::infoList[id].width;
    };
    //get height
    int Texture::height() {
        return Texture::infoList[id].height;
    };
    //get gl texture
    GLuint Texture::glTexture() {
        return Texture::infoList[id].texture;
    }

    std::vector<TextureInfo> Texture::infoList = {};
    uint32_t Texture::textureCounter = 0;

} // ASEngine