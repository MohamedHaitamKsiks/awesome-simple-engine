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
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    }

    //on surface change
    void Renderer::surfaceChange(int width, int height) {
        glViewport(0, 0, width, height);
    }

    mat3 transform = mat3::identity() * mat3::scale(vec2{128.0f, 128.0f}) * mat3::rotation(0.12f);

    //draw frame
    void Renderer::draw() {
        glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        //use default material
        Material::use("mt_default");
        //get position attribute
        int vPosition = glGetAttribLocation(Material::current.glProgram, "vPosition");
        glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(vPosition);
        //get texture coordinates attribute
        int vTextureCoord = glGetAttribLocation(Material::current.glProgram, "vTextureCoord");
        glVertexAttribPointer(vTextureCoord, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(vTextureCoord);
        //pass view
        Material::current.setShaderParam("uView", Screen::getView());

        //pass transform
        transform = transform * mat3::translate(vec2{0.001f, 0.0002f});
        Material::current.setShaderParam("uTransform", transform);

        Sprite sprite("spr_run");
        Material::current.setShaderParam("texture", sprite.texture);

        // Draw the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    }


} // ASEngine