//
// Created by ksiks_wa3r on 3/1/23.
//

#ifndef MY_APPLICATION_TEXTURE_H
#define MY_APPLICATION_TEXTURE_H

#include <vector>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "../Resource/Image.h"

namespace ASEngine {

    struct TextureInfo {
        GLuint texture;
        int width;
        int height;
        //for each texture we are going to allocate a vertex buffer
    };

    class Texture {
    public:
        uint32_t id;
        //eq;
        inline bool operator==(Texture texture){
            return id == texture.id;
        }
        //init textures
        static void init();
        //terminate textures
        static void terminate();
        //load texture from
        static Texture load(Image& image);
        //destroy
        void destroy();
        //get width
        int width();
        //get height
        int height();
        //get gl texture
        GLuint glTexture();
        //default texture
        static Texture defaultTexture;

    private:
        static std::vector<TextureInfo> infoList;
        static std::vector<uint32_t> freeInfoList;
        static uint32_t textureCounter;
    };


} // ASEngine



#endif //MY_APPLICATION_TEXTURE_H
