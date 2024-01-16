#include "ShaderProgramManager.h"
#include "Renderer/Renderer.h"

namespace ASEngine
{

    ShaderProgramID ShaderProgramManager::Create(ShaderID vertexShaderID, ShaderID fragmentShaderID)
    {
        // create shader program info
        ShaderProgramInfo info{};

        // get shader manager
        ShaderManager* shaderManager = Renderer::GetShaderManager();

        // get vertex shader info
        auto& vertexShaderInfo = shaderManager->GetShaderInfo(vertexShaderID);
        if(vertexShaderInfo.Type != ShaderType::VERTEX)
            throw Exception("Expecting First shaderID to be of type ShaderType::VERTEX");

        // get fragment shader info
        auto &fragmentShaderInfo = shaderManager->GetShaderInfo(fragmentShaderID);
        if (fragmentShaderInfo.Type != ShaderType::FRAGMENT)
            throw Exception("Expecting Second shaderID to be of type ShaderType::FRAGMENT");

        // merge params from vertex and fragment shader
        info.Params.Add(vertexShaderInfo.Params);
        info.Params.Add(fragmentShaderInfo.Params);

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

        // get sampler texture index and location
        uint32_t textureIndex = 0;
        for (auto& [samplerName, samplerInfo]: info.Params.Samplers)
        {
            samplerInfo.TextureIndex = textureIndex;
            samplerInfo.Location = glGetUniformLocation(glProgram, samplerName.GetString().c_str());
            textureIndex++;
        }

    #endif // opengl

        // create uniform buffers
        BufferManager* bufferManager = Renderer::GetBufferManager();

        for (auto& [uniformBufferName, uniformBufferInfo]: info.Params.UniformBuffers)
        {
            uniformBufferInfo.UniformBufferID = bufferManager->Create(BufferType::UNIFORM_BUFFER);
        }

        return m_ShaderProgramInfos.Push(info);
    }

    void ShaderProgramManager::Bind(ShaderProgramID shaderProgramID)
    {
        if (m_CurrentShaderProgram == shaderProgramID)
            return;

    #ifdef OPENGL
        auto &shaderProgramInfo = GetShaderProgramInfo(shaderProgramID);
        glUseProgram(shaderProgramInfo.GLProgramID);

        BufferManager *bufferManager = Renderer::GetBufferManager();

        // bind all uniform buffers to respective binding
        for (auto &[uniformBufferName, uniformBufferInfo] : shaderProgramInfo.Params.UniformBuffers)
        {
            auto &bufferInfo = bufferManager->GetBufferInfo(uniformBufferInfo.UniformBufferID);
            glBindBufferBase(GL_UNIFORM_BUFFER, uniformBufferInfo.Binding, bufferInfo.GLBufferID);
        }
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

} // namespace ASEngine
