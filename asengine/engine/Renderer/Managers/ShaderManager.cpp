#include "ShaderManager.h"

namespace ASEngine
{
    ShaderID ShaderManager::Create(const std::string &shaderCode, ShaderType type)
    {
        ShaderInfo info{};
        info.Type = type;

    // create opengl shader
    #ifdef OPENGL
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
            Debug::Error(message);
            throw ShaderCompileFailException();
        }

        info.GLShaderID = shader;
    #endif // OPENGL

        // add info and return ID
        return m_ShaderInfos.Push(info);
    }

    void ShaderManager::Delete(ShaderID shaderID)
    {
    // delete opengl shader
    #ifdef OPENGL
        glDeleteShader(GetShaderInfo(shaderID).GLShaderID);
    #endif
        // delete shader id
        m_ShaderInfos.Free(shaderID);
    }

} // namespace ASEngine
