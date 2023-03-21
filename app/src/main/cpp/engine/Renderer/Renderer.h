//
// Created by ksiks_wa3r on 3/1/23.
//

#ifndef MY_APPLICATION_RENDERER_H
#define MY_APPLICATION_RENDERER_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "../log.h"
#include "../Resource/Material.h"
#include "../Resource/Sprite.h"
#include "Screen.h"

namespace ASEngine {

    class Renderer {
    public:
        //rendering main functions
        static void init();
        static void surfaceChange(int width, int height);
        static void draw();

        //before start quad make sure to use the correct material
        //between start and end quad we can add our params
        /*
        //init quad
        static void quadStart();
        //end quad
        static void quadEnd();

        //draw functions
        static void drawRectangle(vec2 position, vec2 size);
        static void drawTexture(Texture texture, vec2 position, vec2 scale, float rotation);
        static void drawSprite(SpriteID spriteId, int frame,vec2 position, vec2 scale, float rotation);*/
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
