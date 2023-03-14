//
// Created by ksiks_wa3r on 3/14/23.
//

#ifndef MY_APPLICATION_IMAGE_H
#define MY_APPLICATION_IMAGE_H

#include <cstdlib>
#include <string>

struct Image {
    char* pixels;
    int width;
    int height;
    //load image .png
    static Image load(std::string& imagePath) {
        Image image;

        //do stuff

        return  image;
    }
    //free image
    void destroy() {
        free(pixels);
    };
};

#endif //MY_APPLICATION_IMAGE_H
