#define OPENGL

#include "Renderer.h"
#include "Viewport.h"
#include "Core/Window/Window.h"

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

        // init current buffers to be bound later
        m_CurrentVertexBuffers[VertexInputRate::VERTEX] = CHUNK_NULL;
        m_CurrentVertexBuffers[VertexInputRate::INSTANCE] = CHUNK_NULL;

        // conenct to resize signal
        std::function<void(int, int)> callback = [this](int width, int height)
        {
            OnWindowChangeSize(width, height);
        };
        m_ResizeSignalConnection = Window::ResizeSignal().Connect(callback);
    }

    Renderer::~Renderer()
    {
        Window::ResizeSignal().Disconnect(m_ResizeSignalConnection);
    }

    void Renderer::DrawElements(BufferID vertexBufferID, BufferID indexBufferID, size_t indexCount, size_t instanceCount)
    {

    #ifdef OPENGL
        // OpenGL Specification
        BufferManager* bufferManager = Renderer::GetBufferManager();

        const auto &indexBufferInfo = bufferManager->GetBufferInfo(indexBufferID);
        const auto &vertexBufferInfo = bufferManager->GetBufferInfo(vertexBufferID);

        glBindBuffer(vertexBufferInfo.GLBufferType, vertexBufferInfo.GLBufferID);
        glBindBuffer(indexBufferInfo.GLBufferType, indexBufferInfo.GLBufferID);

        //get shader program

        // bind vertex attributes
        auto &vertexAttributes = shaderProgramInfo.VertexAttributes[VertexAttributeInputRate::VERTEX];
        for (auto &vertexAttribute : vertexAttributes)
        {
            switch (vertexAttribute.Type)
            {
            case VertexAttributeType::FLOAT:
                glVertexAttribPointer(vertexAttribute.Location, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (const void *)offsetof(Vertex3D, Position));
                break;

            default:
                break;
            }
            glEnableVertexAttribArray(vPosition);
        }

        // instance drawing
        if (instanceCount > 1)
            glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr, instanceCount);
        else
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    #endif // OPENGL
    }

    void Renderer::BindVertexBuffer(VertexInputRate inputRate, BufferID vertexBufferID)
    {
        if (m_CurrentVertexBuffers[inputRate] == buffer)
    }

    void Renderer::BindIndexBuffer(BufferID indexBufferID)
    {
    }

    void Renderer::DrawElements(size_t instanceCount)
    {
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
        m_BufferManager = std::make_unique<BufferManager>();
        m_ShaderManager = std::make_unique<ShaderManager>();
        m_ShaderProgramManager = std::make_unique<ShaderProgramManager>();
        m_TextureManager = std::make_unique<TextureManager>();
    }
    
    void Renderer::OnWindowChangeSize(int width, int height)
    {
        // ...
    }
} // namespace ASEngine
