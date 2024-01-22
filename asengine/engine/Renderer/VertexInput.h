#ifndef ASENGINE_VERTEX_INPUT_H
#define ASENGINE_VERTEX_INPUT_H

#include "Core/Memory/DynamicArray.h"
#include <cstdint>


namespace ASEngine
{
    // vertex attribute types
    enum class VertexAttributeType
    {
        INT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4,
    };

    // input rate (vetex | instance)
    enum class VertexInputRate
    {
        VERTEX,
        INSTANCE
    };

    // descriptor for one vertex attribute to for a speficific shader
    struct VertexAttribute
    {
        uint32_t Location;
        VertexAttributeType Type;
        size_t Offset;
    };

    // vertex input layout
    struct VertexInputLayout
    {
        size_t Stride;
        VertexInputRate InputRate;
        TDynamicArray<VertexAttribute> VertexAttributes{2};
    };

} // namespace ASEngine


#endif // 