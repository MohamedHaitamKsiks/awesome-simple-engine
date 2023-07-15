
#ifndef ASENGINE_TEXTURE_H
#define ASENGINE_TEXTURE_H

#include <vector>
#include <algorithm>
#include <cstdint>

#ifdef __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#else
#include <GL/glew.h>

#endif

#include "engine/Resource/Image.h"
#include "engine/Log/Log.h"

namespace ASEngine {

    struct TextureInfo {
        GLuint texture = UINT32_MAX;
        int width = -1;
        int height = -1;
        //for each texture we are going to allocate a vertex buffer
    };

    class Texture {
    public:
        uint32_t id = UINT32_MAX;

        Texture(uint32_t _id) {
            id = _id;
        };

        //eq;
        bool operator==(Texture texture) {
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



#endif //ASENGINE_TEXTURE_H
