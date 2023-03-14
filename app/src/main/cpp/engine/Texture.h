//
// Created by ksiks_wa3r on 3/1/23.
//

#ifndef MY_APPLICATION_TEXTURE_H
#define MY_APPLICATION_TEXTURE_H

#include <vector>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

struct TextureInfo {
    GLuint texture;
    int width;
    int height;
};

struct Texture {
    unsigned int id;
    static std::vector<TextureInfo> info;
    //load texture from
    static void load(char* pixels, int width, int height);
    //destroy
    void destroy();
    //get width
    int width() {
        return Texture::info[id].width;
    };
    //get height
    int height() {
        return Texture::info[id].height;
    };
    //get gl texture
    GLuint glTexture() {
        return Texture::info[id].texture;
    };
};

#endif //MY_APPLICATION_TEXTURE_H
