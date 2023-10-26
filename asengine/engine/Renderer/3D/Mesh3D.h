#ifndef ASENGINE_MESH3D_H
#define ASENGINE_MESH3D_H

#include "Core/Memory/DynamicArray.h"
#include "Core/Memory/PoolAllocator.h"
#include "Core/Math/mat4.h"

#include "Renderer/GraphicsAPI.h"
#include "Renderer/Color.h"

#include "Vertex3D.h"

#include <cstddef>

namespace ASEngine
{
    // mesh id
    using Mesh3D = ChunkID;

    // mesh info 3d 
    struct MeshInfo3D
    {
        // vertex data
        TDynamicArray<Vertex3D> Vertices{};
        // index data
        TDynamicArray<uint32_t> Indices{};
        
        // transform mesh
        void Transform(const mat4& transform);

        // combine with other mesh (static batch rendering)
        void Add(const MeshInfo3D& mesh3D);

        // combine with other mesh and transform them (static batch rendering)
        void AddTransformed(const MeshInfo3D &mesh3D, const mat4 &transform);
    };

} // ASEngine

#endif // ASENGINE_MESH3D_H
