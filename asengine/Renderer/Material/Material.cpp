#include "Material.h"

#include "Macros/Foreach.h"

#include "Core/Math/Vector2.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix3x3.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Error/Assertion.h"

#include "Renderer/Color.h"
#include "Renderer/Shader/ShaderParams.h"

#include "Resource/ResourceRefSerialization.h"


// macros to implement uniform buffer type
#define ASENGINE_IMPLEMENT_UNIFORM_BUFFER_IDENTIFIER_TYPE(Type) \
    template void Material::SetShaderParam<Type>(UniqueString uniformName, UniqueString fieldName, const Type &value); \
    template const Type &Material::GetShaderParam<Type>(UniqueString uniformName, UniqueString fieldName) const;

// define resource ref
ASENGINE_SERIALIZE_RESOURCE_REF(Material);

namespace ASEngine
{
    // deserialize uniform field and set

    template <typename T>
    void Material::DeserializeAndSet(const Json &object, UniqueString uniformName, UniqueString fieldName)
    {
        T value{};
        Serializer<T>::Deserialize(object, value);
        SetShaderParam(uniformName, fieldName, value);
    }

    // serialiazation start
    template<>
    void Serializer<Material>::Deserialize(const Json& object, Material& dest)
    {
        // create the material
        ResourceRef<Shader> shader = ResourceRef<Shader>::NONE();
        Serializer<ResourceRef<Shader>>::Deserialize(object.at("Shader"), shader);
        dest.Create(shader);

        // set material data
        // uniform buffers
        const auto& uniformBufferObjects = object.at("UniformBuffers");
        for (const auto& [uniformBufferName, uniformBufferObject]: uniformBufferObjects.items())
        {
            UniqueString ubUniqueString{uniformBufferName}; // cache unique string to
            const ShaderParams& params = shader->GetShaderParams();
            const ShaderUniformBufferInfo& uniformBufferInfo = params.UniformBuffers.at(ubUniqueString);
            
            // identifiers
            for (const auto& [identifierName, identifierValue]: uniformBufferObject.items())
            {
                UniqueString iUniqueString{identifierName}; // cache unique string

                // get identifier info
                const ShaderUniformBufferIdentifier& identifier = uniformBufferInfo.Identifiers.at(iUniqueString);

                // deserialize identifier
                Material::ParamType type = Material::GetIdentifierParamType(identifier);
                switch (type)
                {
                // boolean
                case Material::ParamType::BOOLEAN:
                    dest.DeserializeAndSet<bool>(object, ubUniqueString, iUniqueString);
                    break;

                // int
                case Material::ParamType::INT:
                    dest.DeserializeAndSet<int>(object, ubUniqueString, iUniqueString);
                    break;

                // uint
                case Material::ParamType::UINT:
                    dest.DeserializeAndSet<uint32_t>(object, ubUniqueString, iUniqueString);
                    break;

                // float
                case Material::ParamType::FLOAT:
                    dest.DeserializeAndSet<float>(object, ubUniqueString, iUniqueString);
                    break;

                // vector2
                case Material::ParamType::VECTOR2:
                    dest.DeserializeAndSet<Vector2>(object, ubUniqueString, iUniqueString);
                    break;

                // vector3
                case Material::ParamType::VECTOR3:
                    dest.DeserializeAndSet<Vector3>(object, ubUniqueString, iUniqueString);
                    break;

                // color
                case Material::ParamType::COLOR:
                    dest.DeserializeAndSet<Color>(object, ubUniqueString, iUniqueString);
                    break;

                // matrix3x3
                case Material::ParamType::MATRIX3X3:
                    dest.DeserializeAndSet<Matrix3x3>(object, ubUniqueString, iUniqueString);
                    break;

                // matrix4x4
                case Material::ParamType::MATRIX4X4:
                    dest.DeserializeAndSet<Matrix4x4>(object, ubUniqueString, iUniqueString);
                    break;

                // undefined
                default:
                    ASENGINE_ASSERT(false, "Invalid Identifier Type!");
                    break;
                }

            } 
        }

        // samplers
    }

    template <>
    Json Serializer<Material>::Serialize(const Material &material)
    {
        return Json({});
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Material);
    // end serialiazation
    
    void Material::Create(ResourceRef<Shader> shader)
    {
        // get shader uniform buffer info
        const ShaderParams &shaderParams = m_Shader->GetShaderParams();

        // create byte buffers for each uniform buffer
        for (const auto& [uniformBufferName, uniformBufferInfo]: shaderParams.UniformBuffers)
        {
            ByteBuffer uniformDataBuffer{uniformBufferInfo.Size};
            m_UniformBuffers[uniformBufferName] = std::move(uniformDataBuffer);
        }

        // init textures
        for (const auto& [samplerName, samplerInfo]: shaderParams.Samplers)
        {
            m_Samplers[samplerName] = ResourceRef<Texture>::NONE();
        }

        // set shader
        m_Shader = shader;
    }

    Material::ParamType Material::GetIdentifierParamType(const ShaderUniformBufferIdentifier &identifier)
    {
        ParamType type = ParamType::UNKNOWN;

        // test identifier info to get type
        // boolean
        if (identifier.Type == ShaderIdentifierType::BOOLEAN)
        {
            type = ParamType::BOOLEAN;
        }
        // int
        else if (identifier.Type == ShaderIdentifierType::INT)
        {
            type = ParamType::INT;
        }
        // uint
        else if (identifier.Type == ShaderIdentifierType::UINT)
        {
            type = ParamType::UINT;
        }
        // float
        else if (identifier.Type == ShaderIdentifierType::FLOAT && identifier.VectorSize == 1 && identifier.Columns == 1)
        {
            type = ParamType::FLOAT;
        }
        // vector2
        else if (identifier.Type == ShaderIdentifierType::FLOAT && identifier.VectorSize == 2 && identifier.Columns == 1)
        {
            type = ParamType::VECTOR2;
        }
        // vector3
        else if (identifier.Type == ShaderIdentifierType::FLOAT && identifier.VectorSize == 3 && identifier.Columns == 1)
        {
            type = ParamType::VECTOR3;
        }
        // color
        else if (identifier.Type == ShaderIdentifierType::FLOAT && identifier.VectorSize == 4 && identifier.Columns == 1)
        {
            type = ParamType::COLOR;
        }
        // matrix3x3
        else if (identifier.Type == ShaderIdentifierType::FLOAT && identifier.VectorSize == 3 && identifier.Columns == 3)
        {
            type = ParamType::MATRIX3X3;
        }
        // matrix4x4
        else if (identifier.Type == ShaderIdentifierType::FLOAT && identifier.VectorSize == 4 && identifier.Columns == 4)
        {
            type = ParamType::MATRIX4X4;
        }

        return type;
    }

    // uniform buffer type check
    template <>
    bool Material::CheckParamType<bool>(ParamType type)
    {
        return type == ParamType::BOOLEAN;
    }

    template <>
    bool Material::CheckParamType<int>(ParamType type)
    {
        return type == ParamType::INT;
    }

    template <>
    bool Material::CheckParamType<uint32_t>(ParamType type)
    {
        return type == ParamType::UINT;
    }

    template <>
    bool Material::CheckParamType<float>(ParamType type)
    {
        return type == ParamType::FLOAT;
    }

    template <>
    bool Material::CheckParamType<Vector2>(ParamType type)
    {
        return type == ParamType::VECTOR2;
    }

    template <>
    bool Material::CheckParamType<Vector3>(ParamType type)
    {
        return type == ParamType::VECTOR3;
    }

    template <>
    bool Material::CheckParamType<Color>(ParamType type)
    {
        return type == ParamType::COLOR;
    }

    template <>
    bool Material::CheckParamType<Matrix3x3>(ParamType type)
    {
        return type == ParamType::MATRIX3X3;
    }

    template <>
    bool Material::CheckParamType<Matrix4x4>(ParamType type)
    {
        return type == ParamType::MATRIX4X4;
    }

    // set shader param template
    template <typename T>
    void Material::SetShaderParam(UniqueString uniformName, UniqueString fieldName, const T& value)
    {
        // get param info
        const ShaderParams& shaderParams = m_Shader->GetShaderParams();
        const ShaderUniformBufferInfo& uniformBufferInfo = shaderParams.UniformBuffers.at(uniformName);
        const ShaderUniformBufferIdentifier& identifier = uniformBufferInfo.Identifiers.at(fieldName);

        // check type
        ASENGINE_ASSERT(CheckUniformBufferIdentifierType<T>(identifier), "Identifier type missmatch");

        // push data
        ByteBuffer& dataBuffer = m_UniformBuffers[uniformName];
        dataBuffer.SetDataAt(&value, sizeof(T), identifier.Offset);
    }

    
    // get shader params
    template <typename T>
    const T &Material::GetShaderParam(UniqueString uniformName, UniqueString fieldName) const
    {
        // get param info
        const ShaderParams &shaderParams = m_Shader->GetShaderParams();
        const ShaderUniformBufferInfo &uniformBufferInfo = shaderParams.UniformBuffers.at(uniformName);
        const ShaderUniformBufferIdentifier &identifier = uniformBufferInfo.Identifiers.at(fieldName);

        // check type
        ASENGINE_ASSERT(CheckUniformBufferIdentifierType<T>(identifier), "Identifier type missmatch");

        // push data
        const ByteBuffer &dataBuffer = m_UniformBuffers.at(uniformName);
        return *reinterpret_cast<const T*>(reinterpret_cast<const uint8_t*>(dataBuffer.GetData()) + identifier.Offset); // unsafe
    }

    // add implementations for each type
    FOREACH(ASENGINE_IMPLEMENT_UNIFORM_BUFFER_IDENTIFIER_TYPE, 
        bool,
        int,
        uint32_t,
        float,
        Vector2,
        Vector3,
        Color,
        Matrix3x3,
        Matrix4x4
    )
} // namespace ASEngine
