#ifndef ASENGINE_QUAD_2D_H
#define ASENGINE_QUAD_2D_H

#include <cstdint>

#include "Core/Math/mat3.h"
#include "Core/Math/vec2.h"

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

        // default
        Quad2D() {};

        // create normal quad
        Quad2D(const vec2& size, const mat3& transform, const Color& modulate);

        // create quad width frames
        Quad2D(const vec2 &size, const mat3 &transform, const Color &modulate, int hFrame, int hFrames, int vFrame, int vFrames);
    };

} // namespace ASEngine



#endif // ASENGINE_QUAD_2D_H