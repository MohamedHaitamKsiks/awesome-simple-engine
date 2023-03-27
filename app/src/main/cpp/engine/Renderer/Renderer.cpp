//
// Created by ksiks_wa3r on 3/1/23.
//

#include "Renderer.h"

namespace ASEngine {

    //definition of quad vertex and index data
    //no need for a mesh system since everything will be a quad at the end of the day
    GLfloat Renderer::vertexData[] = {
            //position        uv
            0.0f, 0.0f,     0.0f, 0.0f,
            0.0f, 1.0f,     0.0f, 1.0f,
            1.0f, 1.0f,     1.0f, 1.0f,
            1.0f, 0.0f,     1.0f, 0.0f
    };

    //index data
    GLushort Renderer::indexData[] = {
            0, 1, 2, 2, 3, 0
    };

    //buffers
    uint32_t Renderer::vertexBuffer = 0;
    uint32_t Renderer::indexBuffer = 0;

    Camera camera{};

    //rendering main functions
    //init renderer
    void Renderer::init() {
        //enable blend
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //load quad mesh into the vertex buffer
        glGenBuffers(1, &Renderer::vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, Renderer::vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, 4 * 4 * 4, Renderer::vertexData, GL_STATIC_DRAW);

        glGenBuffers(1, &Renderer::indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Renderer::indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * 2 * 4, Renderer::indexData, GL_STATIC_DRAW);

        ALOG("vertex data loaded");
        //set clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        Camera::current = &camera;
    }

    float time = 0.0f;

    //draw frame
    void Renderer::draw() {
        glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		//use default material
        Material::use("mt_default");

    }



} // ASEngine