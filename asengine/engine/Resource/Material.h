

#ifndef ASENGINE_MATERIAL_H
#define ASENGINE_MATERIAL_H

#include <unordered_map>
#include <string>
#include <vector>
#include <cstring>

#include "Core/Math/mat3.h"
#include "Core/Math/vec2.h"
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
        Material(){}
        ~Material();

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
            
        }

        //set sampler
        void SetSampler(UniqueString samplerName, TextureID textureID);

        // get shader
        inline ResourceID GetShaderID() const
        {
            return m_ShaderID;
        };


    private:
        // copy buffer to material's uniform buffer
        void CopyToUniformBuffer(const void *buffer, size_t offset, size_t size);

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
