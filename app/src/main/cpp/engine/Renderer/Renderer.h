//
// Created by ksiks_wa3r on 3/1/23.
//

#ifndef MY_APPLICATION_RENDERER_H
#define MY_APPLICATION_RENDERER_H

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "../log.h"
#include "../Resource/Material.h"
#include "../Resource/Sprite.h"
#include "Camera.h"

#include "Color.h"
#include "Screen.h"

namespace ASEngine {

    class Renderer {
    public:
        static void init();
        static void draw();

        //before start quad make sure to use the correct material
        //between start and end quad we can add our params

    private:

        //quad mesh definition (all we need for out engine since we are mainly working with sprites)
        //vertex data
        static GLfloat vertexData[];

        //index data
        static GLushort indexData[];

        //buffers
        static uint32_t vertexBuffer;
        static uint32_t indexBuffer;


    };

} // ASEngine

#endif //MY_APPLICATION_RENDERER_H
