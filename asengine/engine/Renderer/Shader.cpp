#include "Shader.h"

namespace ASEngine
{
    // shader params
    ShaderParam::ShaderParam(int _uniformLocation)
    {
        uniformLocation = _uniformLocation;
    }
    // set value
    void ShaderParam::setValue(int _value)
    {
        glUniform1i(uniformLocation, _value);
    }

    void ShaderParam::setValue(float _value)
    {
        glUniform1f(uniformLocation, _value);
    }

    void ShaderParam::setValue(const vec2 &_value)
    {
        glUniform2fv(uniformLocation, 1, (GLfloat *)&_value);
    }

    void ShaderParam::setValue(const Color &_value)
    {
        glUniform4fv(uniformLocation, 1, (GLfloat *)&_value);
    }

    void ShaderParam::setValue(const mat3 &_value)
    {
        glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, _value.data);
    }

    void ShaderParam::setValue(Texture _value)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _value.glTexture());
        glUniform1i(uniformLocation, 0);
        
    }

    // shader
    Shader Shader::current = Shader();

    Shader Shader::getCurrent()
    {
        return current;
    }

    GLuint Shader::loadShader(GLenum shaderType, const char *shaderCode)
    {
        GLuint shader = glCreateShader(shaderType);
        // compile shader
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        // error
        GLint compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE)
        {
            GLsizei log_length = 0;
            GLchar message[1024];
            glGetShaderInfoLog(shader, 1024, &log_length, message);
            // Write the error to a log
            Log::out(message);
            return -1;
        }
        return shader;
    }

    bool Shader::create(const std::string &vertexCode, const std::string &fragmentCode)
    {
        // add precision mediump float for platform devices
        #ifdef __ANDROID__
        std::string newFragmentCode = "precision mediump float;\n" + fragmentCode;
        GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, newFragmentCode.c_str());
        #else
        GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
        #endif

        GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexCode.c_str());
        
        
        if (vertexShader < 0 || fragmentShader < 0)
            return false;
        // create gl es program for shaders
        glProgram = glCreateProgram();
        // attach shaders
        glAttachShader(glProgram, vertexShader);
        glAttachShader(glProgram, fragmentShader);
        // creates OpenGL ES program executables
        glLinkProgram(glProgram);
        Log::out("glProgram created");
        
        return true;
    }

    void Shader::use()
    {
        glUseProgram(glProgram);
        current = *this;
    }

    ShaderParam Shader::getShaderParam(const std::string &param)
    {
        int uniformLocation = glGetUniformLocation(glProgram, param.c_str());
        return ShaderParam(uniformLocation);
    }

    void Shader::destroy()
    {
        glDeleteProgram(glProgram);
    }

} // namespace ASEngine
