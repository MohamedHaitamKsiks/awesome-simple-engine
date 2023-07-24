#include "ShaderUniform.h"

namespace ASEngine
{
    void ShaderUniform::SetInt(const int* value)
    {
        glUniform1i(m_UniformLocation, *value);
    }

    void ShaderUniform::SetFloat(const float* value)
    {
        glUniform1f(m_UniformLocation, *value);
    }

    void ShaderUniform::SetVec2(const float *value)
    {
        glUniform2fv(m_UniformLocation, 1, (GLfloat *) value);
    }

    void ShaderUniform::SetVec3(const float *value)
    {
        glUniform3fv(m_UniformLocation, 1, (GLfloat *)value);
    }

    void ShaderUniform::SetVec4(const float *value)
    {
        glUniform4fv(m_UniformLocation, 1, (GLfloat *)value);
    }

    void ShaderUniform::SetMat3(const float *value)
    {
        glUniformMatrix3fv(m_UniformLocation, 1, GL_TRUE, (GLfloat *)value);
    }
} // namespace ASEngine
