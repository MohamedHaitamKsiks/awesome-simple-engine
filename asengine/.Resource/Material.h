

#ifndef ASENGINE_MATERIAL_H
#define ASENGINE_MATERIAL_H

#include <unordered_map>
#include <string>
#include <vector>
#include <cstring>

#include "Core/Log/Log.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Memory/ByteBuffer.h"

#include "Renderer/Color.h"

#include "ResourceManager.h"
#include "Resource.h"
#include "Shader.h"

namespace ASEngine {

    class Material : public Resource
    {
    public:
        // create material based on file
        bool Load(const std::string& path);
    
        // create material based on shade
        void Create(ResourceID shaderID);

        // bind material before drawing
        void Bind();

        // set uniform buffer
        void SetUniformBuffer(UniqueString uniformBufferName, const ByteBuffer& buffer);

        // set uniform buffer param
        template<typename T>
        void SetUniformBufferParam(UniqueString uniformBufferName, UniqueString paramName, const T& value)
        {
            auto &shader = ResourceManager<Shader>::Get(m_ShaderID);
            ShaderProgramID shaderProgramID = shader.m_ShaderProgramID;

            // get sahder param identifier
            ShaderProgramManager *shaderProgramManager = Renderer::GetShaderProgramManager();
            auto& shaderProgramInfo = shaderProgramManager->GetShaderProgramInfo(shaderProgramID);
            auto& paramIdentifier = shaderProgramInfo.Params.UniformBuffers[uniformBufferName].Identifiers[paramName];

            // set buffer
            auto& uniformBuffer = m_UniformBuffers[uniformBufferName];
            uniformBuffer.SetDataAt(&value, sizeof(T), paramIdentifier.Offset);
        }

        //set sampler
        void SetSampler(UniqueString samplerName, TextureID textureID);

        // get shader
        inline ResourceID GetShaderID() const
        {
            return m_ShaderID;
        };


    private:
        // deserialize and set
        template<typename T>
        void DeserializeAndSet( UniqueString param, const Json& paramValue)
        {
            /*T value;
            Serializer<T>::Deserialize(paramValue, value);
            SetShaderParam(param, value);*/
        }

        // shader
        ResourceID m_ShaderID = CHUNK_NULL;
        
        // param values  
        std::unordered_map<UniqueString, ByteBuffer> m_UniformBuffers{};
        std::unordered_map<UniqueString, TextureID> m_Samplers{};

        friend class Serializer<Material>;
    };



} // ASEngine

#endif //ASENGINE_MATERIAL_H
