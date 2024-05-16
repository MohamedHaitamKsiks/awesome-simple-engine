#include "Shader.h"
#include "Renderer/2D/Vertex2D.h"
#include "Renderer/3D/Vertex3D.h"
#include <unordered_map>

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

    bool Shader::Create(const std::string &vertexPath, const std::string &fragmentPath, ShaderType type)
    {
        // load spirvs
        SpirvBinary vertexSpirv = LoadSpirv(vertexPath);
        SpirvBinary fragmentSpirv = LoadSpirv(fragmentPath);

        // create shaders
        ShaderManager* shaderManager = Renderer::GetShaderManager();

        m_VertexShaderID = shaderManager->Create(vertexSpirv, ShaderStage::VERTEX);
        m_FragmentShaderID = shaderManager->Create(fragmentSpirv, ShaderStage::FRAGMENT);
        
        // get shader layout
        std::unordered_map<VertexInputRate, VertexInputLayout> vertexInputLayouts{};
        
        switch (type)
        {
        case ShaderType::SHADER_2D:
            vertexInputLayouts[VertexInputRate::VERTEX] = Vertex2D::GetVertexInputLayout();
            break;

        case ShaderType::SHADER_3D:
            vertexInputLayouts[VertexInputRate::VERTEX] = Vertex3D::GetVertexInputLayout();
            
            vertexInputLayouts[VertexInputRate::INSTANCE] = VertexInputLayout{};
            vertexInputLayouts[VertexInputRate::INSTANCE].Stride = sizeof(Matrix4x4);
            vertexInputLayouts[VertexInputRate::INSTANCE].InputRate = VertexInputRate::INSTANCE;
            for (uint32_t i = 0; i < 4; i++)
            {
                vertexInputLayouts[VertexInputRate::INSTANCE].VertexAttributes.Push(VertexAttribute{
                    .Location = i + 4,
                    .Type = VertexAttributeType::VEC4,
                    .Offset = i * 4 * sizeof(float)
                });
            }
            break;
        }

        // create shader program
        ShaderProgramManager* shaderProgramManager = Renderer::GetShaderProgramManager();
        m_ShaderProgramID = shaderProgramManager->Create(m_VertexShaderID, m_FragmentShaderID, vertexInputLayouts);

        return true;
    }

    bool Shader::Load(const std::string &path)
    {
        // read file
        File file;
        if (!file.Open(path, FileOpenMode::READ)) 
            return false;
            
        std::string shader = file.ReadText();
        file.Close();



        return true;
    }

    void Shader::Bind()
    {
        Renderer::GetShaderProgramManager()->Bind(m_ShaderProgramID);
    }

    SpirvBinary Shader::LoadSpirv(const std::string &spirvPath)
    {
        // load spirv
        SpirvBinary spirv{};

        File spirvFile;
        spirvFile.Open(spirvPath, FileOpenMode::READ);

        size_t spirvSize = spirvFile.GetSize() / sizeof(uint32_t);
        auto spirvData = std::make_unique<uint32_t[]>(spirvSize);
        spirvFile.Read(reinterpret_cast<char *>(spirvData.get()));

        for (int i = 0; i < spirvSize; i++)
        {
            spirv.push_back(spirvData[i]);
        }

        return spirv;
    }

} // namespace ASEngine
