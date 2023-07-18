#ifndef ASENGINE_MESH_2D_H
#define ASENGINE_MESH_2D_H

#include "Vertex2D.h"

namespace ASEngine
{
    struct Quad2D
    {
        Vertex2D Vertices[4];
        static const Indices[6] = {0, 1, 2, 2, 3, 0};
    };
} // namespace ASEngine



#endif // ASENGINE_MESH_2D_H