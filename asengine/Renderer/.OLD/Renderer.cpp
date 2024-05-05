#include "Renderer.h"
#include "Viewport.h"
#include "Core/Window/Window.h"

namespace ASEngine
{
    void Renderer::Init()
    {
    #pragma region OPENGL_SPECIFICATION
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

    #pragma endregion OPENGL_SPECIFICATION

        // init current buffers to be bound later
        m_CurrentVertexBuffers[VertexInputRate::VERTEX] = CHUNK_NULL;
        m_CurrentVertexBuffers[VertexInputRate::INSTANCE] = CHUNK_NULL;

        // conenct to resize signal
        std::function<void(int, int)> callback = [this](int width, int height)
        {
            OnWindowChangeSize(width, height);
        };
        m_ResizeSignalConnection = Window::GetInstance().GetResizeSignal().Connect(callback);
    }

    void Renderer::Terminate()
    {
        Window::GetInstance().GetResizeSignal().Disconnect(m_ResizeSignalConnection);
    }

    void Renderer::DrawElements(uint32_t indexCount, size_t instanceCount)
    {
    #pragma region OPENGL_SPECIFICATION
        // OpenGL Specification

        // bind vertex attributes
        ShaderProgramManager *shaderProgramManager = Renderer::GetShaderProgramManager();
        auto &shaderProgramInfo = shaderProgramManager->GetShaderProgramInfo(shaderProgramManager->CurrentShaderProgramID());

        auto &vertexInputLayout = shaderProgramInfo.VertexInputLayouts[VertexInputRate::VERTEX];

        for (auto &vertexAttribute : vertexInputLayout.VertexAttributes)
        {
            switch (vertexAttribute.Type)
            {
            case VertexAttributeType::FLOAT:
                glVertexAttribPointer(vertexAttribute.Location, 1, GL_FLOAT, GL_FALSE, vertexInputLayout.Stride, (void *)vertexAttribute.Offset);
                break;
            case VertexAttributeType::VEC2:
                glVertexAttribPointer(vertexAttribute.Location, 2, GL_FLOAT, GL_FALSE, vertexInputLayout.Stride, (void *)vertexAttribute.Offset);
                break;
            case VertexAttributeType::VEC3:
                glVertexAttribPointer(vertexAttribute.Location, 3, GL_FLOAT, GL_FALSE, vertexInputLayout.Stride, (void *)vertexAttribute.Offset);
                break;
            case VertexAttributeType::VEC4:
                glVertexAttribPointer(vertexAttribute.Location, 4, GL_FLOAT, GL_FALSE, vertexInputLayout.Stride, (void *)vertexAttribute.Offset);
                break;
            case VertexAttributeType::INT:
                glVertexAttribPointer(vertexAttribute.Location, 1, GL_INT, GL_FALSE, vertexInputLayout.Stride, (void *)vertexAttribute.Offset);
                break;
            }
            glEnableVertexAttribArray(vertexAttribute.Location);
        }

        BufferManager* bufferManager = Renderer::GetBufferManager();

        const auto &indexBufferInfo = bufferManager->GetBufferInfo(m_CurrentIndexBuffer);
        const auto &vertexBufferInfo = bufferManager->GetBufferInfo(m_CurrentVertexBuffers[VertexInputRate::VERTEX]);

        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferInfo.GLBufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferInfo.GLBufferID);

        // instance drawing
        if (instanceCount > 1)
            glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr, instanceCount);
        else
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    #pragma endregion OPENGL_SPECIFICATION // OPENGL

    }

    void Renderer::BindVertexBuffer(VertexInputRate inputRate, BufferID vertexBufferID)
    {
        m_CurrentVertexBuffers[inputRate] = vertexBufferID;
    }

    void Renderer::BindIndexBuffer(BufferID indexBufferID)
    {
        m_CurrentIndexBuffer = indexBufferID;
    }

    void Renderer::Clear()
    {
    // OpenGL Specification
    #pragma region OPENGL_SPECIFICATION
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    #pragma endregion OPENGL_SPECIFICATION // OPENGL
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
        // get aspect ratio of viewport
        float viewportAspectRatio = Viewport::GetSize().x / Viewport::GetSize().y;

        // get aspect ratio of window
        float windowAspectRatio = (float)width / (float)height;
   
    #pragma region OPENGL_SPECIFICATION
        // same aspect ratio
        float precision = 0.0001f;
        if (abs(viewportAspectRatio - windowAspectRatio) < precision)
        {
            // recompute viewport
            glViewport(0, 0, width, height);
        }
        // window larger than viewport
        else if (windowAspectRatio > viewportAspectRatio)
        {
            // get new width
            int newWidth = (int)(viewportAspectRatio * height);
            int viewportPosition = (width - newWidth) / 2;
            glViewport(viewportPosition, 0, newWidth, height);
        }
        // window longuer than viewport
        else
        {
            // get new height
            int newHeight = (int)(width / viewportAspectRatio);
            int viewportPosition = (height - newHeight) / 2;
            glViewport(0, viewportPosition, width, newHeight);
        }
    #pragma endregion OPENGL_SPECIFICATION
    }
} // namespace ASEngine
