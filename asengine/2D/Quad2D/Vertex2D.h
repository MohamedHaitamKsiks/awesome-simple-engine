#ifndef __ASENGINE_VERTEX_2D_H
#define __ASENGINE_VERTEX_2D_H

#include "Core/Math/Vector2.h"
#include "Renderer/Color.h"

#include "API/API.h"

namespace ASEngine
{
    // base definition of vertex 2D
    struct ASENGINE_API Vertex2D
    {
        Vector2 Position;
        Vector2 TextureCoord;
        Color Modulate;
    };
} // namespace ASEngine


#endif // __ASENGINE_VERTEX_2D_H