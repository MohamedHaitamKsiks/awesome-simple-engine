#ifndef ASENGINE_SHADER_PARAMS_H
#define ASENGINE_SHADER_PARAMS_H

#include <vector>
#include <cstdint>

#include "Core/String/UniqueString.h"
#include "Renderer/Buffer/Buffer.h"
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
        ResourceRef<Buffer> UniformBufferID{};

        // shader layout
        std::unordered_map<UniqueString, ShaderUniformBufferIdentifier> Identifiers{};
    };

    // 

} // namespace ASEngine


#endif // ASENGINE_SHADER_IDENTIFIER_H