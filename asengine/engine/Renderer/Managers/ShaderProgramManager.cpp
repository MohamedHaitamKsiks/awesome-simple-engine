#include "ShaderProgramManager.h"

namespace ASEngine
{
    void ShaderProgramInfo::FetchUniforms()
    {
    // opengl specification
    #ifdef OPENGL

        // get uniform count
        int uniformCount;
        glGetProgramiv(m_GLProgram, GL_ACTIVE_UNIFORMS, &uniformCount);

        // fetch uniforms
        int offset = 0;
        for (int i = 0; i < uniformCount; i++)
        {
            // bake info
            ShaderUniformInfo uniformInfo{};
            uniformInfo.Offset = offset;

            // get uniform info
            constexpr size_t SHADER_UNIFORM_NAME_MAX_LENGTH = 15;
            GLchar name[SHADER_UNIFORM_NAME_MAX_LENGTH];
            GLint size;
            GLenum type;
            
            glGetActiveUniform(this->GLProgramID, static_cast<GLuint>(i), SHADER_UNIFORM_NAME_MAX_LENGTH, nullptr, &size, &type, name);
            
            uniformInfo.GLUniformLocation = glGetUniformLocation(this->GLProgramID, name);
            uniformInfo.Name = UniqueString(name);

            // bake type
            switch (type)
            {
            case GL_INT:
                uniformInfo.Type = ShaderUniformType::INT;
                uniformInfo.Size = sizeof(int);
                break;
            case GL_FLOAT:
                uniformInfo.Type = ShaderUniformType::FLOAT;
                uniformInfo.Size = sizeof(float);
                break;
            case GL_FLOAT_VEC2:
                uniformInfo.Type = ShaderUniformType::VEC2;
                uniformInfo.Size = sizeof(float[2]);
                break;
            case GL_FLOAT_VEC3:
                uniformInfo.Type = ShaderUniformType::VEC3;
                uniformInfo.Size = sizeof(float[3]);
                break;
            case GL_FLOAT_VEC4:
                uniformInfo.Type = ShaderUniformType::VEC4;
                uniformInfo.Size = sizeof(float[4]);
                break;
            case GL_FLOAT_MAT3:
                uniformInfo.Type = ShaderUniformType::MAT3;
                uniformInfo.Size = sizeof(float[9]);
                break;
            case GL_FLOAT_MAT4:
                uniformInfo.Type = ShaderUniformType::MAT4;
                uniformInfo.Size = sizeof(float[16]);
                break;
            case GL_SAMPLER_2D:
                uniformInfo.Type = ShaderUniformType::SAMPLER_2D;
                uniformInfo.Size = sizeof(int);
                break;

            default:
                uniformInfo.Type = ShaderUniformType::UNDEFINED;
                break;
            }

            // push unifrom info
            offset += uniformInfo.Size;
            this->UniformInfos[uniformInfo.Name] = uniformInfo;
        }

    #endif // OPENGL
    }

    ShaderProgramManager::ShaderProgramManager(ShaderManager *shaderManager)
    {
        m_ShaderManager = shaderManager;
        // excpect shader manager to be non null
        ASSERT(m_ShaderManager, "Shader Program Manager requires non null ShaderManager");
    }

    ShaderProgramID ShaderProgramManager::Create(ShaderID vertexShaderID, ShaderID fragmentShaderID)
    {
        // create shader program info
        ShaderProgramInfo info{};
        //info.Type = ShaderType::VERTEX | ShaderType::FRAGMENT;
        
        // get vertex shader info
        auto& vertexShaderInfo = m_ShaderManager->GetShaderInfo(vertexShaderID);
        if(vertexShaderInfo.Type != ShaderType::VERTEX)
            throw Exception("Expecting First shaderID to be of type ShaderType::VERTEX");

        // get fragment shader info
        auto &fragmentShaderInfo = m_ShaderManager->GetShaderInfo(fragmentShaderID);
        if (fragmentShaderInfo.Type != ShaderType::FRAGMENT)
            throw Exception("Expecting Second shaderID to be of type ShaderType::FRAGMENT");

    // opengl specification
    #ifdef OPENGL

        // create gl es program for shaders
        GLuint glProgram = glCreateProgram();
        
        // attach shaders
        glAttachShader(glProgram, vertexShaderInfo.GLShaderID);
        glAttachShader(glProgram, fragmentShaderInfo.GLShaderID);

        // creates OpenGL program
        glLinkProgram(glProgram);
        info.GLProgramID = glProgram;

    #endif // opengl

        info.FetchUniforms();
        return m_ShaderProgramInfos.Push(info);
    }

    void ShaderProgramManager::Bind(ShaderProgramID shaderProgramID)
    {
        if (m_CurrentShaderProgram == shaderProgramID)
            return;

    #ifdef OPENGL
        auto &shaderProgramInfo = GetShaderProgramInfo(shaderProgramID);
        glUseProgram(shaderProgramInfo.GLProgramID);
    #endif // OPENGL

        m_CurrentShaderProgram = shaderProgramID;
    }

    void ShaderProgramManager::Destroy(ShaderProgramID shaderProgramID)
    {
    #ifdef OPENGL
        auto& shaderProgramInfo = GetShaderProgramInfo(shaderProgramID);
        glDeleteProgram(shaderProgramInfo.GLProgramID);
    #endif // OPENGL
        m_ShaderProgramInfos.Free(shaderProgramID);
    }

    /*
    template <>
    void ShaderProgramManager::SetUniformValue<int>(UniqueString uniformName, const int &value)
    {
    #ifdef OPENGL
        auto& uniformInfo = GetUniformInfo(m_CurrentShaderProgram, uniformName);
        glUniform1i(uniformInfo.GLUniformLocation, value);
    #endif // OPENGL
    }

    template <>
    void ShaderProgramManager::SetUniformValue<float>(UniqueString uniformName, const float &value)
    {
    #ifdef OPENGL
        auto &uniformInfo = GetUniformInfo(m_CurrentShaderProgram, uniformName);
        glUniform1f(uniformInfo.GLUniformLocation, value);
    #endif // OPENGL
    }

    template <>
    void ShaderProgramManager::SetUniformValue<vec2>(UniqueString uniformName, const vec2 &value)
    {
    #ifdef OPENGL
        auto &uniformInfo = GetUniformInfo(m_CurrentShaderProgram, uniformName);
        glUniform2fv(uniformInfo.GLUniformLocation, 1, reinterpret_cast<GLfloat*>(&value));
    #endif // OPENGL
    }

    template <>
    void ShaderProgramManager::SetUniformValue<vec3>(UniqueString uniformName, const vec3 &value)
    {
    #ifdef OPENGL
        auto &uniformInfo = GetUniformInfo(m_CurrentShaderProgram, uniformName);
        glUniform3fv(uniformInfo.GLUniformLocation, 1, reinterpret_cast<GLfloat *>(&value));
    #endif // OPENGL
    }

    template <>
    void ShaderProgramManager::SetUniformValue<Color>(UniqueString uniformName, const Color &value)
    {
    #ifdef OPENGL
        auto &uniformInfo = GetUniformInfo(m_CurrentShaderProgram, uniformName);
        glUniform4fv(uniformInfo.GLUniformLocation, 1, reinterpret_cast<GLfloat *>(&value));
    #endif // OPENGL
    }

    template <>
    void ShaderProgramManager::SetUniformValue<mat3>(UniqueString uniformName, const mat3 &value)
    {
    #ifdef OPENGL
        auto &uniformInfo = GetUniformInfo(m_CurrentShaderProgram, uniformName);
        glUniformMatrix3fv(uniformInfo.GLUniformLocation, 1, GL_TRUE, reinterpret_cast<GLfloat *>(&value));
    #endif // OPENGL
    }

    template <>
    void ShaderProgramManager::SetUniformValue<mat4>(UniqueString uniformName, const mat4 &value)
    {
    #ifdef OPENGL
        auto &uniformInfo = GetUniformInfo(m_CurrentShaderProgram, uniformName);
        glUniformMatrix4fv(uniformInfo.GLUniformLocation, 1, GL_TRUE, reinterpret_cast<GLfloat *>(&value));
    #endif // OPENGL
    }

    */
} // namespace ASEngine
