//
// Created by ksiks_wa3r on 3/1/23.
//

#ifndef MY_APPLICATION_RENDERER_H
#define MY_APPLICATION_RENDERER_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>


namespace ASEngine {

    class Renderer {
    public:
        //rendering main functions
        static void init();
        static void surfaceChange(int width, int height);
        static void draw();
    private:


    };

} // ASEngine

#endif //MY_APPLICATION_RENDERER_H
