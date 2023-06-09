//
// Created by ksiks_wa3r on 3/20/23.
//

#ifndef MY_APPLICATION_SCREEN_H
#define MY_APPLICATION_SCREEN_H

#include "../Math/mat3.h"

namespace ASEngine {

    class Screen {
    public:
        //size
        static void setSize(int _width, int height);
        static int getWidth();
        static int getHeight();

        //window size
        static void setWindowSize(int _width, int _height);
        static int getWindowWidth();
        static int getWindowHeight();

        static vec2 getSize();
        static vec2 getCenter();

        //get matrix
        static mat3 getView();


    private:
        //size
        static int width;
        static int height;

        //real size
        static int windowWidth;
        static int windowHeight;


    };

} // ASEngine

#endif //MY_APPLICATION_SCREEN_H
