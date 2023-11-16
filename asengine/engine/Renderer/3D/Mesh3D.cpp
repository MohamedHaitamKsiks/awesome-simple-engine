#include "Mesh3D.h"

namespace ASEngine
{

    void MeshInfo3D::Transform(const mat4 &transform)
    {
        for (int i = 0; i < Vertices.GetSize(); i++)
        {
            Vertices[i].Position = transform * Vertices[i].Position;
        }
    }

    void MeshInfo3D::Add(const MeshInfo3D &mesh3D)
    {   
        uint32_t indexOffset = Vertices.GetSize();

        // push vertices   
        for (int i = 0; i < mesh3D.Vertices.GetSize(); i++)
        {
            Vertices.Push(mesh3D.Vertices[i]);
        }

        // push indicies
        for (int i = 0; i < mesh3D.Indices.GetSize(); i++)
        {
            Indices.Push(mesh3D.Indices[i] + indexOffset);
        }
    }

    void MeshInfo3D::AddTransformed(const MeshInfo3D &mesh3D, const mat4 &transform)
    {
        MeshInfo3D transformedMesh = mesh3D;
        transformedMesh.Transform(transform);
        Add(transformedMesh);
    }
    
} // namespace ASEngine

