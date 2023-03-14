//
// Created by ksiks_wa3r on 3/13/23.
//

#ifndef MY_APPLICATION_MATERIAL_H
#define MY_APPLICATION_MATERIAL_H

#include "Renderer.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

struct Material {
    int glProgram;
    //load shader
    static GLuint loadShader(GLenum shaderType, const char* shaderCode) {
        GLuint shader = glCreateShader(shaderType);
        //compile shader
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        return shader;
    }
    //load material
    static Material load(const char* vertexCode, const char* fragmentCode) {
        //load shaders
        GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexCode);
        GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentCode);
        //create gl es program for shaders
        GLuint glProgram = glCreateProgram();
        //attach shaders
        glAttachShader(glProgram, vertexShader);
        glAttachShader(glProgram, fragmentShader);
        // creates OpenGL ES program executables
        glLinkProgram(glProgram);
        //create material
        Material material{};
        material.glProgram = glProgram;
        return material;
    };
    //use material
    static void use(Material material) {
        glUseProgram(material.glProgram);
    }
};

#endif //MY_APPLICATION_MATERIAL_H
