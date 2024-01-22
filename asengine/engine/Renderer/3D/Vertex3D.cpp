#include "Vertex3D.h"

namespace ASEngine
{
    VertexInputLayout Vertex3D::GetVertexInputLayout()
    {
        VertexInputLayout vertexInputLayout{};
        vertexInputLayout.InputRate = VertexInputRate::VERTEX;
        vertexInputLayout.Stride = sizeof(Vertex3D);

        vertexInputLayout.VertexAttributes = TDynamicArray<VertexAttribute>{2};

        // Position
        vertexInputLayout.VertexAttributes.Push(VertexAttribute{
            .Location = 0,
            .Type = VertexAttributeType::VEC3,
            .Offset = offsetof(Vertex3D, Position),
        });

        // Normal
        vertexInputLayout.VertexAttributes.Push(VertexAttribute{
            .Location = 1,
            .Type = VertexAttributeType::VEC3,
            .Offset = offsetof(Vertex3D, Normal),
        });

        // UV
        vertexInputLayout.VertexAttributes.Push(VertexAttribute{
            .Location = 2,
            .Type = VertexAttributeType::VEC2,
            .Offset = offsetof(Vertex3D, UV),
        });

        // Modulate
        vertexInputLayout.VertexAttributes.Push(VertexAttribute{
            .Location = 3,
            .Type = VertexAttributeType::VEC4,
            .Offset = offsetof(Vertex3D, Modulate),
        });

        return vertexInputLayout;
    }

} // namespace ASEngine
