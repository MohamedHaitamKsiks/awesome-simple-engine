#include "Renderer.h"

namespace ASEngine
{
    void Renderer::Render()
    {
        m_DrawCallsCount = 0;
    }

    void Renderer::BindVertexBuffer(VertexInputRate inputRate, ResourceRef<Buffer> vertexBuffer)
    {
        // don't bind if already bound
        if (m_CurrentVertexBuffer.find(inputRate) != m_CurrentVertexBuffer.end() && m_CurrentVertexBuffer[inputRate] == vertexBuffer)
            return;

        BindVertexBufferImp(inputRate, vertexBuffer);
        m_CurrentVertexBuffer[inputRate] = vertexBuffer;
    }

    void Renderer::BindIndexBuffer(ResourceRef<Buffer> indexBuffer)
    {
        if (m_CurrentIndexBuffer == indexBuffer)
            return;

        BindIndexBufferImp(indexBuffer);
        m_CurrentIndexBuffer = indexBuffer;
    }

    void Renderer::DrawElements(uint32_t indexCount, uint32_t instanceCount)
    { 
        DrawElementsImp(indexCount, instanceCount);
        m_DrawCallsCount++;
    }

    void Renderer::BindShader(ResourceRef<Shader> shader)
    {
        if (m_CurrentShader == shader)
            return;

        BindShaderImp(shader);
        m_CurrentShader = shader;
    }
} // namespace ASEngine
