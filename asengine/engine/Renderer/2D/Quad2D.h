#ifndef ASENGINE_MESH_2D_H
#define ASENGINE_MESH_2D_H

#include <cstdint>

#include "engine/Math/mat3.h"
#include "engine/Math/vec2.h"

#include "Vertex2D.h"

#define QUAD_2D_VERTICES_COUNT 4
#define QUAD_2D_INDICES_COUNT 6

namespace ASEngine
{
    struct Quad2D
    {
        // quad vertices
        Vertex2D Vertices[QUAD_2D_VERTICES_COUNT];
        // quad indicies
        constexpr static const uint16_t Indices[QUAD_2D_INDICES_COUNT] = {0, 1, 2, 2, 3, 0};

        // create normal quad
        Quad2D(vec2& size, mat3& transform, const Color& modulate);
        
    };

} // namespace ASEngine



#endif // ASENGINE_MESH_2D_H