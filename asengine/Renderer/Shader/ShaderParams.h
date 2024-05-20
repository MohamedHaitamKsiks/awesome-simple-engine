#ifndef ASENGINE_SHADER_PARAMS_H
#define ASENGINE_SHADER_PARAMS_H

#include <vector>
#include <cstdint>

#include "Core/String/UniqueString.h"
#include "Resource/ResourceRef.h"

namespace ASEngine
{
    // shader identifier base types
    enum class ShaderIdentifierType
    {
        UNDEFINED = 0,
        BOOLEAN,
        INT,
        UINT,
        FLOAT
    };

    // all data of a shader uniform buffer identifier
    struct ShaderUniformBufferIdentifier
    {
        ShaderIdentifierType Type = ShaderIdentifierType::UNDEFINED;               // type
        UniqueString Name;                       // name
        size_t Offset;                           // offset in bytes in the buffer
        size_t VectorSize;                       // more than 1 => it's a vector
        size_t Columns;                          // more than 1 => it's a matrix
        std::vector<size_t> ArrayDimentions{}; // more than 1 element multidimentional array, more than 1 => it's an array
    };

    // uniform buffer info
    struct ShaderUniformBufferInfo
    {
        uint32_t Binding = 0;
        size_t Size = 0;
        // shader layout
        std::unordered_map<UniqueString, ShaderUniformBufferIdentifier> Identifiers{};
    };

    // shader sampler infos
    struct ShaderSamplerInfo
    {
        UniqueString Name;
        uint32_t Binding;
    };

    // shader params 
    struct ShaderParams
    {
        std::unordered_map<UniqueString, ShaderUniformBufferInfo> UniformBuffers = {};
        std::unordered_map<UniqueString, ShaderSamplerInfo> Samplers = {};

        // combine two shader params and return the result
        static ShaderParams Combine(const ShaderParams& a, const ShaderParams& b);
    };

} // namespace ASEngine


#endif // ASENGINE_SHADER_IDENTIFIER_H