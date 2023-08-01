#include "Quad2D.h"

namespace ASEngine
{
    Quad2D::Quad2D(const vec2 &size, const mat3 &transform, const Color &modulate)
    {   
        Vertices[0] = Vertex2D{transform * vec2{0.0f, 0.0f}, vec2{0.0f, 0.0f}, modulate},
        Vertices[1] = Vertex2D{transform * vec2{size.x, 0.0f}, vec2{1.0f, 0.0f}, modulate},
        Vertices[2] = Vertex2D{transform * vec2{size.x, size.y}, vec2{1.0f, 1.0f}, modulate},
        Vertices[3] = Vertex2D{transform * vec2{0.0f, size.y}, vec2{0.0f, 1.0f}, modulate};
    }

    Quad2D::Quad2D(const vec2 &size, const mat3 &transform, const Color &modulate, int hFrame, int hFrames, int vFrame, int vFrames)
    {
        vec2 frames = vec2{ 1.0f / (float)hFrames, 1.0f / (float)vFrames };
        vec2 frame = vec2{ (float)hFrame / (float)hFrames, (float)vFrame / (float)vFrames };

        Vertices[0] = Vertex2D{transform * vec2{0.0f, 0.0f}, frame + frames * vec2{0.0f, 0.0f}, modulate},
        Vertices[1] = Vertex2D{transform * vec2{size.x, 0.0f}, frame + frames * vec2{1.0f, 0.0f}, modulate},
        Vertices[2] = Vertex2D{transform * vec2{size.x, size.y}, frame + frames * vec2{1.0f, 1.0f}, modulate},
        Vertices[3] = Vertex2D{transform * vec2{0.0f, size.y}, frame + frames * vec2{0.0f, 1.0f}, modulate};
    }
} // namespace ASEngine
