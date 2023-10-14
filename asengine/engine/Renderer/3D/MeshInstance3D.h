#ifndef ASENGINE_MESH_INSTANCE_3D_H
#define ASENGINE_MESH_INSTANCE_3D_H

#include "Core/Memory/DynamicArray.h"
#include "Core/Memory/PoolAllocator.h"
#include "Core/Math/mat4.h"

#include "Renderer/GraphicsAPI.h"
#include "Renderer/Color.h"

#include "Resource/Material.h"

#include "Mesh3D.h"
#include "Vertex3D.h"

#include <cstddef>

namespace ASEngine
{
    using MeshInstance3D = ChunkID;

    // one or multiple mesh instances
    struct MeshInstanceInfo3D
    {
        Mesh3D Mesh;
        ResourceID MaterialID;
        mat4 Transform;
    };

} // ASEngine

#endif // ASENGINE_MESH_INSTANCE_3D_H
