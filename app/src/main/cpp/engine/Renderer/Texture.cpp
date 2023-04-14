//
// Created by ksiks_wa3r on 3/18/23.
//
#include "Texture.h"

namespace ASEngine {

    Texture Texture::defaultTexture = Texture{};

    //init
    void Texture::init() {
        //load default texture
        Image defaultImage = Image::load("images/no_texture.png");
        defaultTexture = Texture::load(defaultImage);
        defaultImage.destroy();
		//log
		ALOG("Texture init complete");
    };

    //terminate
    void Texture::terminate() {
        //delete all textures
        for (int i = 0; i < infoList.size(); i++) {
			//check if texture id is free
			if (std::count(freeInfoList.begin(), freeInfoList.end(), i))
				continue;
			//if not you delete the texture
            glDeleteTextures(1, &infoList[i].texture);
        }
		//erase vectors
		infoList.clear();
		freeInfoList.clear();
        //texture counter
        textureCounter = 0;
    };

    //load texture from
    Texture Texture::load(Image& image) {
        //create GL texture
        GLuint texture;
        //load open gl texture
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //image format
        switch (image.format) {
            case IMAGE_FORMAT_RBGA:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.pixels);
                break;
            case IMAGE_FORMAT_GRAYSCALE:
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, image.width, image.height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, image.pixels);
                break;
            case IMAGE_FORMAT_GRAYSCALE_ALPHA:
                glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, image.width, image.height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, image.pixels);
                break;
        }

        //create texture info
        TextureInfo info{texture, image.width, image.height};
        //check if there is some free space in the infoList
        if (Texture::freeInfoList.size()){
            uint32_t freeId = Texture::freeInfoList[Texture::freeInfoList.size() - 1];
            Texture::freeInfoList.pop_back();
            Texture::infoList[freeId] = info;
            return Texture{freeId};
        }
        Texture::infoList.push_back(info);
        //return texture
        Texture loadedTexture{Texture::textureCounter};
        Texture::textureCounter++;
        //log
        ALOG("Texture created: %d", texture);
        return loadedTexture;
    }
    //destroy
    void Texture::destroy() {
        //delete gl texture
        GLuint textures[] = {glTexture()};
        glDeleteTextures(1, textures);
        //instead of deleting the texture from the vector i'm going to add it to the free indecies
        //this will not screw with the order while conserving a little bit the memory
        Texture::freeInfoList.push_back(id);
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
    std::vector<uint32_t> Texture::freeInfoList = {};
    uint32_t Texture::textureCounter = 0;



} // ASEngine