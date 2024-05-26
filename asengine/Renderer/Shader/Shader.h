#ifndef ASENGINE_SHADER_H
#define ASENGINE_SHADER_H

#include <unordered_map>

#include "ShaderParams.h"
#include "ShaderSource.h"

#include "Renderer/VertexInput/VertexInputDescriptor.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Texture/Texture.h"

#include "Resource/ResourceRef.h"
#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"
#include "Resource/ResourceSerialization.h"

#include "Core/String/UniqueString.h"
#include "Core/Memory/ByteBuffer.h"

namespace ASEngine
{
    // abstarct class represention of a shader
    // shader is created with a vertex shader code and a fragment shader code
    class Shader: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(Shader);
    ASENGINE_SERIALIZE_RESOURCE(Shader);
    public:
        virtual ~Shader() {};

        // create shader from vertex and fragment shaders
        void Create(ResourceRef<ShaderSource> vertexSource, ResourceRef<ShaderSource> fragmentSource, ResourceRef<VertexInputDescriptor> vertexInputDescriptor);

        // set shader uniform buffer's data
        void SetUniformBuffer(UniqueString uniformBufferName, const ByteBuffer& data);

        // set sampler's texture
        void SetSamplerTexture(UniqueString samplerName, ResourceRef<Texture> texture);
        
        // get shader params
        inline const ShaderParams& GetShaderParams() const
        {
            return m_Params;
        }
    protected:
        // api specific implementations
        virtual void CreateImp(ResourceRef<ShaderSource> vertexSource, ResourceRef<ShaderSource> fragmentSource, ResourceRef<VertexInputDescriptor> vertexInputDescriptor) = 0;

    private:
        // vertex source and fragment
        ResourceRef<ShaderSource> m_VertexSource = ResourceRef<ShaderSource>::NONE();
        ResourceRef<ShaderSource> m_FragmentSource = ResourceRef<ShaderSource>::NONE();

        // shader params here 
        ShaderParams m_Params{}; // cache params info for faster access
        std::unordered_map<UniqueString, ResourceRef<Buffer>> m_UniformBuffers{};
        std::unordered_map<UniqueString, ResourceRef<Texture>> m_Samplers{};

        // vertex input layouts
        std::unordered_map<VertexInputRate, VertexInputLayout> m_VertexInputLayouts{};
    };
} // namespace ASEngine


#endif // ASENGINE_SHADER_H