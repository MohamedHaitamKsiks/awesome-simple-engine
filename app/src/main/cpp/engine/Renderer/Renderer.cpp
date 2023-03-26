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

    //on surface change
    void Renderer::surfaceChange(int width, int height) {
        glViewport(0, 0, width, height);
    }

    float time = 0.0f;

    //draw frame
    void Renderer::draw() {
        glClear (GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        //use default material
        Material::use("mt_default");
        Camera::current->position.x = time;
        Camera::current->zoom = 1.0f + 0.5f * cos(time) ;

        vec2 center = vec2{130.0f, 240.0f};
        for (int i = 0; i < 32; i++)
            drawSprite("spr_run", (int) time, vec2{32.0f * i, 32.0f * i}, vec2::one(), time * 0.2f);

        time += 0.12f;

    }

    void Renderer::quadStart() {
        //get position attribute
        int vPosition = glGetAttribLocation(Material::current.glProgram, "vPosition");
        glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(vPosition);
        //get texture coordinates attribute
        int vTextureCoord = glGetAttribLocation(Material::current.glProgram, "vTextureCoord");
        glVertexAttribPointer(vTextureCoord, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
        glEnableVertexAttribArray(vTextureCoord);
        //pass view
        Material::current.setShaderParam("view", Screen::getView());
        //pass camera
        Material::current.setShaderParam("camera", Camera::current->getMatrix());
    }

    void Renderer::quadEnd() {
        // Draw the triangle
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
    }

    void Renderer::drawTexture(Texture texture, vec2 position, vec2 scale, float rotation) {
        quadStart();
        //1 frame
        Material::current.setShaderParam("hframe", 0);
        Material::current.setShaderParam("hframes", 1);
        Material::current.setShaderParam("vframe", 0);
        Material::current.setShaderParam("vframes", 1);

        //transform matrix
        vec2 imageScale = vec2{ (float)texture.width(), (float)texture.height() };
        mat3 transform =
                mat3::translate(position) *
                mat3::rotation(rotation) *
                mat3::scale(scale) *
                mat3::scale(imageScale);

        Material::current.setShaderParam("transform", transform);

        quadEnd();
    }

    void Renderer::drawSprite(SpriteID spriteId, int frame, vec2 position, vec2 scale, float rotation) {
        //get sprite
        Sprite sprite = spriteId;

        //draw
        quadStart();
        //1 frame
        Material::current.setShaderParam("hframe", frame % sprite.frames);
        Material::current.setShaderParam("hframes", sprite.frames);
        Material::current.setShaderParam("vframe", 0);
        Material::current.setShaderParam("vframes", 1);

        //transform matrix
        vec2 imageScale = vec2{ (float)sprite.width, (float)sprite.height };
        mat3 transform =
                mat3::translate(position) *
                mat3::rotation(rotation) *
                mat3::scale(scale) *
                mat3::translate( vec2{-sprite.offset.x, -sprite.offset.y} ) *
                mat3::scale(imageScale) ;

        Material::current.setShaderParam("transform", transform);

        quadEnd();

    }


} // ASEngine