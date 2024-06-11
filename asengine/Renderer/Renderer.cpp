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

    void Renderer::Create(Backend backend)
    {
        switch (backend)
        {
        // opengl
        case Backend::OPENGL:
            RendererBackend::CreateOpenGLRenderer();
            break;
        
        // unsupported backends
        default:
            ExitUnsupportedRenderer(backend);
            break;
        }
    }

    void Renderer::ExitUnsupportedRenderer(Backend backend)
    {
        Json backendObject;
        Serializer::Deserialize(backendObject, backend);
        
        Debug::Error(std::string(backendObject), ": Unsupported backend!");
    }

    void Renderer::Render()
    {
        m_DrawCallsCount = 0;
    }

    void Renderer::BindVertexBuffer(ResourceRef<Buffer> vertexBuffer, uint32_t binding)
    {
        // don't bind if already bound
        if (m_CurrentVertexBuffer.find(binding) != m_CurrentVertexBuffer.end() && m_CurrentVertexBuffer[inputRate] == vertexBuffer)
            return;

        BindVertexBufferImp(vertexBuffer, binding);
        m_CurrentVertexBuffer[binding] = vertexBuffer;
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
        if (m_CurrentMaterial == material)
            return;

        // bind shader of the material
        BindShader(material->GetShader());

    }

    
} // namespace ASEngine
