#include "Shader.h"

namespace ASEngine
{

    Shader::Shader()
    {
        
    }

    Shader::~Shader()
    {
        if (!IsOwner())
            return;

        if (m_Program != SHADER_NULL)
            ShaderProgram::Destroy(m_Program);
    }

    bool Shader::Load(const std::string &shaderFile)
    {
        // read file
        File file;
        file.Open(shaderFile, FileOpenMode::READ);
        std::string shaderCode = file.ReadText();
        file.Close();

        // compile shader code
        m_Program = ShaderProgram::Create(shaderCode);

        // get params
        m_Uniforms = m_Program.GetAllUniformInfo();
        m_UniformNames.reserve(m_Uniforms.size());

        // add params
        for (int i = 0; i < m_Uniforms.size(); i++)
        {
            ShaderUniformInfo info = m_Uniforms[i];
            m_UniformNames.insert_or_assign(info.Name, i);
            m_UniformBufferSize += info.Size;
        }

        return true;
    }

    void Shader::Bind()
    {
        ShaderProgram::Use(m_Program);
        m_Program.BindVertex2D();
    }

} // namespace ASEngine
