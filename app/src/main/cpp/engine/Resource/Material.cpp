//
// Created by ksiks_wa3r on 3/18/23.
//

#include "Material.h"


namespace ASEngine {

    void Material::quadInit() {
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


    //load shader
    GLuint Material::loadShader(GLenum shaderType, const char* shaderCode) {
        GLuint shader = glCreateShader(shaderType);
        //compile shader
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        //error
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetShaderInfoLog(shader, 1024, &log_length, message);
            // Write the error to a log
            ALOG("%s", message);
        }


        return shader;
    }
    //load material
    Material Material::load(std::string name, std::string vertexCode, std::string fragmentCode) {
        //load shaders
        GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexCode.c_str());
        GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
        //create gl es program for shaders
        GLuint glProgram = glCreateProgram();
        //attach shaders
        glAttachShader(glProgram, vertexShader);
        glAttachShader(glProgram, fragmentShader);
        // creates OpenGL ES program executables
        glLinkProgram(glProgram);
        ALOG("glProgram created : %d", glProgram);
        //create material
        Material material{};
        material.glProgram = glProgram;
        //add material
        Material::add(name, material);
        return material;
    };
    //use material
    void Material::use(Material& material) {
        current = material;
        glUseProgram(material.glProgram);
        quadInit();
    };

    void Material::use(MaterialID materialId) {
        Material material = materialId;
        use(material);
    }

    std::unordered_map<ResourceID, Material> Material::materials = {};

    void Material::add(MaterialID materialId, Material &material) {
        material.id = materialId;
        Material::materials[materialId] = material;
    }

    Material Material::current = {};

    //set shader params
    void Material::setShaderParam(std::string param, int value) {
        int uniformLocation = glGetUniformLocation(glProgram, param.c_str());
        glUniform1i(uniformLocation, value);

    }

    void Material::setShaderParam(std::string param, float value) {
        int uniformLocation = glGetUniformLocation(glProgram, param.c_str());
        glUniform1f(uniformLocation, value);
    }

    void Material::setShaderParam(std::string param, vec2 value) {
        int uniformLocation = glGetUniformLocation(glProgram, param.c_str());
        GLfloat values[] = {value.x, value.y};
        glUniform2fv(uniformLocation, 1, values);
    }

    void Material::setShaderParam(std::string param, Color value) {
        int uniformLocation = glGetUniformLocation(glProgram, param.c_str());
        GLfloat values[] = {value.r, value.g, value.b, value.a};
        glUniform4fv(uniformLocation, 1, values);
    }

    void Material::setShaderParam(std::string param, mat3 value) {
        int uniformLocation = glGetUniformLocation(glProgram, param.c_str());
        glUniformMatrix3fv(uniformLocation, 1, GL_TRUE, value.data);
    }

    void Material::setShaderParam(std::string param, Texture value) {
		glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, value.glTexture());
        //ALOG("bind texture %d", value.glTexture());

        int uniformLocation = glGetUniformLocation(glProgram, param.c_str());
        glUniform1i(uniformLocation, 0);
    }

} // ASEngine