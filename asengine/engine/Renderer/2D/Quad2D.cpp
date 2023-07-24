#include "Quad2D.h"

namespace ASEngine
{
    Quad2D::Quad2D(vec2 &size, mat3 &transform, const Color &modulate)
    {
        Vertices[0] = Vertex2D{transform * vec2{0.0f, 0.0f}, vec2{0.0f, 0.0f}, modulate},
        Vertices[1] = Vertex2D{transform * vec2{size.x, 0.0f}, vec2{1.0f, 0.0f}, modulate},
        Vertices[2] = Vertex2D{transform * vec2{size.x, size.y}, vec2{1.0f, 1.0f}, modulate},
        Vertices[3] = Vertex2D{transform * vec2{0.0f, size.y}, vec2{0.0f, 1.0f}, modulate};
    }
} // namespace ASEngine
