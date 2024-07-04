#include "Renderer.h"

#include <cstdlib>

#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Serialization/SerializeEnum.h"

#include "Backend/RendererBackend.h"

namespace ASEngine
{
    ASENGINE_SERIALIZE_ENUM(Renderer::Backend, 
        NONE,
        OPENGL,
        VULKAN
    );

    void Renderer::Init()
    {
        InitImp();
    }

    void Renderer::Terminate()
    {
        TerminateImp();
    }

    void Renderer::BeginRendering()
    {
        m_DrawCallsCount = 0;
    }

    // end rendering = reset bindings
    void Renderer::EndRendering()
    {
        m_CurrentVertexBuffers.clear();

        m_CurrentIndexBuffer = ResourceRef<Buffer>::NONE();
        m_CurrentShader = ResourceRef<Shader>::NONE();
        m_CurrentMaterial = ResourceRef<Material>::NONE();
    }

    void Renderer::BindVertexBuffer(ResourceRef<Buffer> vertexBuffer, uint32_t binding)
    {
        // don't bind if already bound
        if (m_CurrentVertexBuffers.find(binding) != m_CurrentVertexBuffers.end() && m_CurrentVertexBuffers.at(binding) == vertexBuffer)
            return;

        BindVertexBufferImp(vertexBuffer, binding);
        m_CurrentVertexBuffers[binding] = vertexBuffer;
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

    void Renderer::BindMaterial(ResourceRef<Material> material)
    {
        //if (m_CurrentMaterial == material)
        //    return;

        // bind shader of the material
        BindShader(material->GetShader());

        // bind uniform values to shader
        for (auto& [uniformBufferName, byteBuffer]: material->m_UniformBuffers)
        {
            m_CurrentShader->SetUniformBuffer(uniformBufferName, byteBuffer);
        }

        // bind samplers
        for (auto &[samplerName, sampler] : material->m_Samplers)
        {
            m_CurrentShader->SetSamplerTexture(samplerName, sampler);
        }

        m_CurrentMaterial = material;
    }

    
} // namespace ASEngine
