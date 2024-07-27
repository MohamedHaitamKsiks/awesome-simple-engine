#include "Renderer.h"

#include <cstdlib>

#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Serialization/SerializeEnum.h"

#include "Backend/RendererBackend.h"

// check of in rendering context
#define ASSERT_RENDERER_BEGIN() ASENGINE_ASSERT(m_UsingViewport, "Make sure to call begin to render to a viewport or directly to the screen!")

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

    void Renderer::Begin(const ResourceRef<Viewport>& viewport)
    {
        ASENGINE_ASSERT(!m_UsingViewport, "Cannot Begin before closing your current viewport");
        m_UsingViewport = true;

        m_CurrentViewport = viewport;

        BeginImp(viewport);
    }

    void Renderer::End()
    {
        ASENGINE_ASSERT(m_UsingViewport, "Nothing to end");
        m_UsingViewport = false;

        // call imp
        EndImp();

        // unbind all render resources
        m_CurrentViewport = ResourceRef<Viewport>::NONE();

        m_CurrentVertexBuffers.clear();

        m_CurrentIndexBuffer = ResourceRef<Buffer>::NONE();
        m_CurrentShader = ResourceRef<Shader>::NONE();
        m_CurrentMaterial = ResourceRef<Material>::NONE();
    }

    void Renderer::BindVertexBuffer(const ResourceRef<Buffer>& vertexBuffer, uint32_t binding)
    {
        ASSERT_RENDERER_BEGIN();
        // don't bind if already bound
        if (m_CurrentVertexBuffers.find(binding) != m_CurrentVertexBuffers.end() && m_CurrentVertexBuffers.at(binding) == vertexBuffer)
            return;

        BindVertexBufferImp(vertexBuffer, binding);
        m_CurrentVertexBuffers[binding] = vertexBuffer;
    }

    void Renderer::BindIndexBuffer(const ResourceRef<Buffer>& indexBuffer)
    {
        ASSERT_RENDERER_BEGIN();
        if (m_CurrentIndexBuffer == indexBuffer)
            return;

        BindIndexBufferImp(indexBuffer);
        m_CurrentIndexBuffer = indexBuffer;
    }

    void Renderer::DrawElements(uint32_t indexCount, uint32_t instanceCount)
    {
        ASSERT_RENDERER_BEGIN();
        DrawElementsImp(indexCount, instanceCount);
        m_DrawCallsCount++;
    }

    void Renderer::BindShader(const ResourceRef<Shader>& shader)
    {
        ASSERT_RENDERER_BEGIN();
        if (m_CurrentShader == shader)
            return;

        BindShaderImp(shader);
        m_CurrentShader = shader;
    }

    void Renderer::BindMaterial(const ResourceRef<Material>& material)
    {
        ASSERT_RENDERER_BEGIN();

        // bind uniform values to shader
        for (auto& [uniformBufferName, byteBuffer]: material->m_UniformBuffers)
        {
            material->GetShader()->SetUniformBuffer(uniformBufferName, byteBuffer);
        }

        // bind samplers
        for (auto &[samplerName, sampler] : material->m_Samplers)
        {
            material->GetShader()->SetSamplerTexture(samplerName, sampler);
        }

        // bind shader of the material
        BindShader(material->GetShader());

        m_CurrentMaterial = material;
    }


} // namespace ASEngine
