#include "ShaderSource.h"

#include "Resource/ResourceRefSerialization.h"

#include "Core/Error/Assertion.h"
#include "Core/FileSystem/File.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

// use spirv_glsl to read shader params
#include "spirv_glsl.hpp"

ASENGINE_SERIALIZE_RESOURCE_REF(ShaderSource);

#define UNIFORM_BUFFER_LAYOUT_SIZE(size) (size + max(16 - size, 0));


namespace ASEngine
{
    void ShaderSource::Create(const SpirvBinary &spirv)
    {
        // create compiler glsl
        spirv_cross::CompilerGLSL glsl(spirv);

        // get resources
        spirv_cross::ShaderResources resources = glsl.get_shader_resources();

        // get uniform buffers
        for (auto &uniformBuffer : resources.uniform_buffers)
        {
            ShaderUniformBufferInfo ubInfo{};
            ubInfo.Binding = glsl.get_decoration(uniformBuffer.id, spv::DecorationBinding);

            // get type
            const auto &uniformBufferType = glsl.get_type(uniformBuffer.type_id);
            ubInfo.Size = (glsl.get_declared_struct_size(uniformBufferType) / 16 + 1) * 16;

            // get uniform buffer members
            const auto &memberTypes = uniformBufferType.member_types;
            for (uint32_t i = 0; i < memberTypes.size(); i++)
            {
                ShaderUniformBufferIdentifier ubIdentifier{};

                // process type
                const auto &memberType = glsl.get_type(memberTypes[i]);
                const auto &baseMemberType = memberType.basetype;

                // adapt base member type to ShaderIdentifierType
                switch (baseMemberType)
                {
                case spirv_cross::SPIRType::Boolean:
                    ubIdentifier.Type = ShaderIdentifierType::BOOLEAN;
                    break;
                case spirv_cross::SPIRType::Int:
                    ubIdentifier.Type = ShaderIdentifierType::INT;
                    break;
                case spirv_cross::SPIRType::UInt:
                    ubIdentifier.Type = ShaderIdentifierType::UINT;
                    break;
                case spirv_cross::SPIRType::Float:
                    ubIdentifier.Type = ShaderIdentifierType::FLOAT;
                    break;
                default:
                    ubIdentifier.Type = ShaderIdentifierType::UNDEFINED;
                }

                // get vector and cols
                ubIdentifier.VectorSize = static_cast<size_t>(memberType.vecsize);
                ubIdentifier.Columns = static_cast<size_t>(memberType.columns);

                // get array dimentions
                for (auto dimention : memberType.array)
                {
                    ubIdentifier.ArrayDimentions.push_back(dimention);
                }

                // add name and offset
                ubIdentifier.Name = UniqueString(glsl.get_member_name(uniformBufferType.self, i));
                ubIdentifier.Offset = glsl.type_struct_member_offset(uniformBufferType, i);

                // push identifier
                ubInfo.Identifiers[ubIdentifier.Name] = ubIdentifier;
            }

            m_Params.UniformBuffers[UniqueString(uniformBuffer.name)] = ubInfo;
        }

        // get samplers
        for (auto &sampler : resources.sampled_images)
        {
            ShaderSamplerInfo samplerInfo{};
            samplerInfo.Name = UniqueString(sampler.name);
            samplerInfo.Binding = glsl.get_decoration(sampler.id, spv::DecorationBinding);

            m_Params.Samplers[samplerInfo.Name] = samplerInfo;
        }
    }

    bool ShaderSource::Load(const std::string &path)
    {
        SpirvBinary spirv{};

        File spirvFile;
        // all shaders are autamically compiled to spirv with .spv extention added at the end
        if (!spirvFile.Open(path + ".spv", FileOpenMode::READ))
        {
            return false;
        }

        size_t spirvSize = spirvFile.GetSize() / sizeof(uint32_t);
        auto spirvData = std::make_unique<uint32_t[]>(spirvSize);
        spirvFile.Read(reinterpret_cast<char *>(spirvData.get()));

        for (size_t i = 0; i < spirvSize; i++)
        {
            spirv.push_back(spirvData[i]);
        }

        spirvFile.Close();
        Create(spirv);

        m_Spirv = spirv;
        return true;
    }

} // namespace ASEngine
