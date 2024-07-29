#ifndef __ASENGINE_VERTEX_INPUT_H
#define __ASENGINE_VERTEX_INPUT_H

#include <vector>
#include <cstdint>
#include <cstddef>



namespace ASEngine
{
    // vertex attribute types
    enum class VertexAttributeType
    {
        NONE = 0,
        INT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4
    };

    // input rate (vetex | instance)
    enum class VertexInputRate
    {
        NONE = 0,
        VERTEX,
        INSTANCE
    };

    // descriptor for one vertex attribute to for a speficific shader
    struct  VertexAttribute
    {
        uint32_t Location = 0;
        VertexAttributeType Type = VertexAttributeType::NONE;
        size_t Offset = 0;
    };

    // vertex input layout
    struct  VertexInputLayout
    {
        uint32_t Binding = 0;
        size_t Stride = 0;
        VertexInputRate InputRate = VertexInputRate::NONE;
        std::vector<VertexAttribute> VertexAttributes{};
    };

} // namespace ASEngine


#endif //
