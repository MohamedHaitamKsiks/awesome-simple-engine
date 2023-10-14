#ifndef ASENGINE_MESH3D_H
#define ASENGINE_MESH3D_H

#include "Core/Memory/DynamicArray.h"
#include "Core/Memory/PoolAllocator.h"

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

        // combine with other mesh (static batch rendering)
        // void Add(const MeshInfo3D& mesh3D);
    };

} // ASEngine

#endif // ASENGINE_MESH3D_H
