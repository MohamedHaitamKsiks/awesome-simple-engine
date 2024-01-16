#include "Renderer.h"

namespace ASEngine
{
    
    Renderer::Renderer()
    {
    // OpenGL Specification
    #ifdef OPENGL

        // init renderer
        // init glew for desktop devices
        #ifndef __ANDROID__
        glewInit();
        #endif

        // print gpu used
        const GLubyte *deviceName = glGetString(GL_RENDERER);
        Debug::Log("Using Device :", deviceName);

        // enable blend
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // set clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        glEnable(GL_DEPTH_TEST);

    #endif // OPENGL
        // init graphics managers
        InitManagers();
    }

    void Renderer::DrawElements(BufferID vertexBufferID, BufferID indexBufferID, size_t indexCount, size_t instanceCount)
    {
    // OpenGL Specification
        auto* bufferManager = Renderer::GetBufferManager();
        
    
    #ifdef OPENGL
        const auto& indexBufferInfo = bufferManager->GetBufferInfo(indexBufferID);
        const auto& vertexBufferInfo = bufferManager->GetBufferInfo(vertexBufferID);
        
        glBindBuffer(vertexBufferInfo.GLBufferType, vertexBufferInfo.GLBufferID);
        glBindBuffer(indexBufferInfo.GLBufferType, indexBufferInfo.GLBufferID);
        
        if (instanceCount > 1)
            glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr, instanceCount);
        else
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    #endif // OPENGL
    }

    void Renderer::Clear()
    {
    // OpenGL Specification
    #ifdef OPENGL
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    #endif // OPENGL
    }

    void Renderer::InitManagers()
    {
        m_ShaderManager = std::make_unique<ShaderManager>();
        m_ShaderProgramManager = std::make_unique<ShaderProgramManager>(m_ShaderManager.get());
        m_TextureManager = std::make_unique<TextureManager>();
    }
} // namespace ASEngine
