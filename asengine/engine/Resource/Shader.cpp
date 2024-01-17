#include "Shader.h"

namespace ASEngine
{

    Shader::Shader()
    {
        
    }

    Shader::~Shader()
    {
        // delete shader program
        ShaderProgramManager* shaderProgramManager = Renderer::GetShaderProgramManager();
        if (m_ShaderProgramID != CHUNK_NULL)
            shaderProgramManager->Destroy(m_ShaderProgramID);

        // delete shaders
        ShaderManager* shaderManager = Renderer::GetShaderManager();
        if (m_FragmentShaderID != CHUNK_NULL)
            shaderManager->Delete(m_FragmentShaderID);

        if (m_VertexShaderID != CHUNK_NULL)
            shaderManager->Delete(m_VertexShaderID);
        }

    bool Shader::Load(const std::string &path)
    {
        // read file
        File file;
        if (!file.Open(path, FileOpenMode::READ)) 
            return false;
            
        std::string shaderCode = file.ReadText();
        file.Close();

        return true;
    }

    void Shader::Bind()
    {
        Renderer::GetShaderProgramManager()->Bind(m_ShaderProgramID);
    }

} // namespace ASEngine
