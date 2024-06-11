#include "Shader.h"

#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Resource/ResourceRefSerialization.h"

#include "Core/Error/Assertion.h"

ASENGINE_SERIALIZE_RESOURCE_REF(Shader);

namespace ASEngine
{
    template<>
    void Serializer::Deserialize(const Json& object, Shader& dest)
    {
        // load vertex source
        ResourceRef<ShaderSource> vertexSource;
        Serializer::Deserialize(object.at("Vertex"), vertexSource);
        
        // load fragment source
        ResourceRef<ShaderSource> fragmentSource;
        Serializer::Deserialize(object.at("Fragment"), fragmentSource);
        
        // load vertex input descriptor
        ResourceRef<VertexInputDescriptor> vertexInputDescriptor;
        Serializer::Deserialize(object.at("VertexInputDescritor"), vertexInputDescriptor);
        
        // create shader
        dest.Create(vertexSource, fragmentSource, vertexInputDescriptor);
    }

    template<>
    Json Serializer::Serialize(const Shader& value)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Shader);

    void Shader::Create(ResourceRef<ShaderSource> vertexSource, ResourceRef<ShaderSource> fragmentSource, ResourceRef<VertexInputDescriptor> vertexInputDescriptor)
    {
        CreateImp(vertexSource, fragmentSource, vertexInputDescriptor);

        // save sources
        m_VertexSource = vertexSource;
        m_FragmentSource = fragmentSource;

        m_Params = ShaderParams::Combine(vertexSource->GetShaderParams(), fragmentSource->GetShaderParams());

        // create uniform buffers
        for (const auto& [uniformName, uniformBufferInfo]: m_Params.UniformBuffers)
        {
            ResourceRef<Buffer> uniformBuffer = Buffer::GetResourceClass().New();
            uniformBuffer->Create(BufferType::UNIFORM_BUFFER);

            m_UniformBuffers[uniformName] = uniformBuffer; 
        }
        
        // create sampler map
        for (const auto& [samplerName, sampler]: m_Params.Samplers)
        {
            m_Samplers[samplerName] = ResourceRef<Texture>::NONE();
        }
    }
    
    void Shader::SetUniformBuffer(UniqueString uniformBufferName, const ByteBuffer &data)
    {
        ASENGINE_ASSERT(m_UniformBuffers.find(uniformBufferName) != m_UniformBuffers.end(), "Uniform buffer name DO NOT EXIST");
        m_UniformBuffers[uniformBufferName]->SetData(data);
    }
    
    void Shader::SetSamplerTexture(UniqueString samplerName, ResourceRef<Texture> texture)
    {
        ASENGINE_ASSERT(m_Samplers.find(samplerName) != m_Samplers.end(), "Sampler name DO NOT EXIST");
        m_Samplers[samplerName] = texture;
    }

} // namespace ASEngine
