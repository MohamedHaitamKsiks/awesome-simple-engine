

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

        // set shader param
        template<typename T>
        void SetShaderParam(const UniqueString& param, const T& value)
        {
            /*// get shader
            auto &shader = ResourceManager<Shader>::Get(m_ShaderID);
            // get shader info
            int paramIndex = shader.m_UniformNames[param];
            ShaderUniformInfo info = shader.m_Uniforms[paramIndex];

            // check if sizeof T is the same as param info
            if (info.Size != sizeof(T))
            {
                return;
            }

            // copy value to buffer
            CopyToUniformBuffer(&value, info.Offset, sizeof(T));*/
        }

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

} //ASEngine

#endif //ASENGINE_MATERIAL_H
