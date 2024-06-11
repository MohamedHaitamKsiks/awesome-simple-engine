#ifndef __ASENGINE_MATERIAL_H
#define __ASENGINE_MATERIAL_H

#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"
#include "Resource/ResourceRef.h"
#include "Resource/ResourceSerialization.h"

#include "Renderer/Shader/Shader.h"
#include "Renderer/Texture/Texture.h"

namespace ASEngine
{
    class Material: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(Material);
    ASENGINE_SERIALIZE_RESOURCE(Material);
    public:
        ~Material() {}

        // create material from shader
        void Create(ResourceRef<Shader> shader);

        // set texture 
        inline void SetShaderParam(UniqueString textureName, ResourceRef<Texture> texture)
        {
            m_Samplers[textureName] = texture;
        }
    
        // get texture
        inline ResourceRef<Texture> GetShaderParam(UniqueString textureName) const
        {
            return m_Samplers.at(textureName);
        }

        // set uniform buffer value 
        template<typename T>
        void SetShaderParam(UniqueString uniformName, UniqueString fieldName, const T& value);
        
        // get uniform buffer value
        template <typename T>
        const T &GetShaderParam(UniqueString uniformName, UniqueString fieldName) const;

        // get shader
        inline ResourceRef<Shader> GetShader() const
        {
            return m_Shader;
        }
    private:
        ResourceRef<Shader> m_Shader;
        std::unordered_map<UniqueString, ByteBuffer> m_UniformBuffers{};
        std::unordered_map<UniqueString, ResourceRef<Texture>> m_Samplers{};

        // supported types
        enum ParamType
        {
            UNKNOWN = 0,
            BOOLEAN,
            INT,
            UINT,
            FLOAT,
            VECTOR2,
            VECTOR3,
            COLOR,
            MATRIX3X3,
            MATRIX4X4
        };

        // get param type from shader uniform identifer
        static ParamType GetIdentifierParamType(const ShaderUniformBufferIdentifier& identifier);

        // false structo for unsupported template type
        template <typename T>
        struct UniformBufferIdentifierTypeNotSupported: public std::false_type
        {
        };

        // check param type
        template<typename T>
        static bool CheckParamType(ParamType type)
        {
            static_assert(UniformBufferIdentifierTypeNotSupported<T>::value, "Type unsupported"); // always crash compilation if your are checking an unsupported uniform buffer type
            return false;
        }
        
        // check uniform buffer type
        template<typename T>
        static inline bool CheckUniformBufferIdentifierType(const ShaderUniformBufferIdentifier& identifier)
        {
            return CheckParamType<T>(GetIdentifierParamType(identifier));
        }

        // deserialize and set shader param
        template<typename T>
        void DeserializeAndSet(const Json& object, UniqueString uniformName, UniqueString fieldName);
    
        friend class Serializer;
    };
} // namespace ASEngine

#endif //ASENGINE_MATERIAL_H