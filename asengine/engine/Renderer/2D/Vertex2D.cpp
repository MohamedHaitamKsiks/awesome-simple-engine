#include "Vertex2D.h"

namespace ASEngine
{
    VertexInputLayout Vertex2D::GetVertexInputLayout()
    {
        VertexInputLayout vertexInputLayout{};
        vertexInputLayout.InputRate = VertexInputRate::VERTEX;
        vertexInputLayout.Stride = sizeof(Vertex2D);
        
        vertexInputLayout.VertexAttributes = TDynamicArray<VertexAttribute>{2};

        // Position
        vertexInputLayout.VertexAttributes.Push(VertexAttribute{
            .Location = 0,
            .Type = VertexAttributeType::VEC2,
            .Offset = offsetof(Vertex2D, Position),
        });

        // UV
        vertexInputLayout.VertexAttributes.Push(VertexAttribute{
            .Location = 1,
            .Type = VertexAttributeType::VEC2,
            .Offset = offsetof(Vertex2D, UV),
        });

        // Modulate
        vertexInputLayout.VertexAttributes.Push(VertexAttribute{
            .Location = 2,
            .Type = VertexAttributeType::VEC4,
            .Offset = offsetof(Vertex2D, Modulate),
        });

        return vertexInputLayout;
    }

} // namespace ASEngine
