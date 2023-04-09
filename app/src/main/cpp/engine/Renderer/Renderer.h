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
#include "VertexBufferObject.h"

namespace ASEngine {

    class Renderer {
    public:
        static void init();
        static void draw();

    private:
        //I'm using batch rendering as a way to optimise rendering
        //buy reducing the number of draw calls



    };

} // ASEngine

#endif //MY_APPLICATION_RENDERER_H
