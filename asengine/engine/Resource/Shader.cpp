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
    }

    bool Shader::Load(const std::string &path)
    {
        // read file
        File file;
        if (!file.Open(path, FileOpenMode::READ)) return false;
        std::string shaderCode = file.ReadText();
        file.Close();

        /*// compile shader code
        m_Program = ShaderProgram::Create(shaderCode);

        // get params
        m_Uniforms = std::vector(m_Program.GetAllUniformInfo());
        m_UniformNames.reserve(m_Uniforms.size());

        // add params
        for (int i = 0; i < m_Uniforms.size(); i++)
        {
            ShaderUniformInfo info = m_Uniforms[i];
            m_UniformNames.insert({m_Uniforms[i].Name, i});
            m_UniformBufferSize += info.Size;
        }
*/
        return true;
    }

    void Shader::Bind()
    {
        //ShaderProgram::Use(m_Program);
    }

} // namespace ASEngine
