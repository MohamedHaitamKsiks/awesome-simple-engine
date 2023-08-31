#include "ShaderProgram.h"

namespace ASEngine
{
   
    void ShaderProgram::BindVertex2D()
    {
        // get position attribute
        int vPosition = glGetAttribLocation(m_GLProgram, "v_Position");
        glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void *)offsetof(Vertex2D, Position));
        glEnableVertexAttribArray(vPosition);
        // get texture coordinates attribute
        int vTextureCoord = glGetAttribLocation(m_GLProgram, "v_TextureCoord");
        glVertexAttribPointer(vTextureCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void *)offsetof(Vertex2D, UV));
        glEnableVertexAttribArray(vTextureCoord);
        // get modulate attribute
        int vModulate = glGetAttribLocation(m_GLProgram, "v_Modulate");
        glVertexAttribPointer(vModulate, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (const void *)offsetof(Vertex2D, Modulate));
        glEnableVertexAttribArray(vModulate);
    }

    ShaderProgram ShaderProgram::Create(const std::string &shaderCode)
    {

        // get shader codes
        std::string vertexCode = "#version 300 es\n#define VERTEX\n" + shaderCode;
        std::string fragmentCode = "#version 300 es\nprecision mediump float;\n#define FRAGMENT\n" + shaderCode;

        GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());
        GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexCode.c_str());

        if (vertexShader < 0 || fragmentShader < 0)
            return SHADER_NULL;
        // create gl es program for shaders
        GLuint glProgram = glCreateProgram();
        // attach shaders
        glAttachShader(glProgram, vertexShader);
        glAttachShader(glProgram, fragmentShader);
        // creates OpenGL program
        glLinkProgram(glProgram);

        return ShaderProgram(glProgram);
    };

    GLuint ShaderProgram::CompileShader(GLenum shaderType, const char *shaderCode)
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
            Debug::Log(message);
            return -1;
        }
        return shader;
    };

    void ShaderProgram::Destroy(ShaderProgram program)
    {
        glDeleteProgram(program.m_GLProgram);
    }

    void ShaderProgram::Use(ShaderProgram program)
    {
        glUseProgram(program.m_GLProgram);
    }

    ShaderUniform ShaderProgram::GetUniformLocation(const std::string &param)
    {
        int uniformLocation = glGetUniformLocation(m_GLProgram, param.c_str());
        return ShaderUniform(uniformLocation);
    }

    int ShaderProgram::GetUniformCount()
    {
        int count;
        glGetProgramiv(m_GLProgram, GL_ACTIVE_UNIFORMS, &count);
        return count;
    }

    std::vector<ShaderUniformInfo> ShaderProgram::GetAllUniformInfo()
    {
        std::vector<ShaderUniformInfo> infos = {};

        int uniformCount = GetUniformCount();
        int offset = 0;
        

        for (int i = 0; i < uniformCount; i++)
        {
            ShaderUniformInfo info = GetUniformInfo(i);
            info.Offset = offset;

            infos.push_back(info);

            offset += info.Size;
        }

        return infos;
    }

    ShaderUniformInfo ShaderProgram::GetUniformInfo(int index)
    {
        // get unifrom information
        GLchar name[SHADER_UNIFORM_NAME_LENGTH];
        GLint size;
        GLenum type;
        glGetActiveUniform(m_GLProgram, (GLuint) index, SHADER_UNIFORM_NAME_LENGTH, NULL, &size, &type, name);
        ShaderUniform location = GetUniformLocation(name);
        // bake info
        ShaderUniformInfo info = ShaderUniformInfo(location);
        info.Name = UniqueString(name);

        // bake type
        switch (type)
        {
        case GL_INT:
            info.Type = ShaderUniformType::INT;
            info.Size = sizeof(int);
            break;
        case GL_FLOAT:
            info.Type = ShaderUniformType::FLOAT;
            info.Size = sizeof(float);
            break;
        case GL_FLOAT_VEC2:
            info.Type = ShaderUniformType::VEC2;
            info.Size = sizeof(float[2]);
            break;
        case GL_FLOAT_VEC3:
            info.Type = ShaderUniformType::VEC3;
            info.Size = sizeof(float[3]);
            break;
        case GL_FLOAT_VEC4:
            info.Type = ShaderUniformType::VEC4;
            info.Size = sizeof(float[4]);
            break;
        case GL_FLOAT_MAT3:
            info.Type = ShaderUniformType::MAT3;
            info.Size = sizeof(float[9]);
            break;
        case GL_SAMPLER_2D:
            info.Type = ShaderUniformType::SAMPLER_2D;
            info.Size = sizeof(Texture);
            break;

        default:
            info.Type = ShaderUniformType::UNDEFINED;
            break;
        }

        return info;  
    }

} // namespace ASEngine
