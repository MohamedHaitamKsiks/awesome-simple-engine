//
// Created by ksiks_wa3r on 3/1/23.
//

#include "Renderer.h"

namespace ASEngine {

    void Renderer::init() 
    {
        //init glew for desktop devices
        #ifndef __ANDROID__
        glewInit();
        #endif

        //enable blend
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //set clear color
        glClearColor(0.5f, 0.5f, 0.55f, 1.0f);

        //this is temporary
        //I will remove this after I rework the material system
        //init default shader

        File fragmentShaderFile;
        fragmentShaderFile.open("shaders/default.frag", FILE_OPEN_MODE_READ);
        std::string fragmentCode = fragmentShaderFile.readText();
        fragmentShaderFile.close();

        File vertexShaderFile;
        vertexShaderFile.open("shaders/default.vert", FILE_OPEN_MODE_READ);
        std::string vertexCode = vertexShaderFile.readText();
        vertexShaderFile.close();

        defaultShader.create(vertexCode, fragmentCode);

    }


    void Renderer::draw() 
    {
        glClear (GL_COLOR_BUFFER_BIT);
        defaultShader.use();
        defaultShader.getShaderParam("view").setValue(Screen::getView());
        defaultShader.getShaderParam("camera").setValue(Camera::current->getMatrix());
    }   

    Renderer::~Renderer()
    {
        defaultShader.destroy();
    }

} // ASEngine