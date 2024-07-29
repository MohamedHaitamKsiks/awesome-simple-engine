#include "Quad2D.h"
#include "Core/Math/Vector2.h"

namespace ASEngine
{
    Quad2D::Quad2D(const Vector2 &size)
    {
        Create(size, Matrix3x3::IDENTITY(), Color::WHITE(), Vector2::ZERO(), Vector2::ONE());
    }

    Quad2D::Quad2D(const Vector2 &size, const Color &modulate)
    {
        Create(size, Matrix3x3::IDENTITY(), modulate, Vector2::ZERO(), Vector2::ONE());
    }

    Quad2D::Quad2D(const Vector2 &size, const Matrix3x3 &matrix, const Color &modulate)
    {
        Create(size, matrix, modulate, Vector2::ZERO(), Vector2::ONE());
    }

    Quad2D::Quad2D(const Vector2 &size, const Matrix3x3 &matrix, const Color &modulate, const Vector2 &topleft, const Vector2 &botright)
    {
        Create(size, matrix, modulate, topleft, botright);
    }

    void Quad2D::Create(const Vector2 &size, const Matrix3x3 &matrix, const Color &modulate, const Vector2 &topleft, const Vector2 &botright, const Vector2& offset)
    {
        Vertices[0] = Vertex2D{matrix * offset, topleft, modulate};
        Vertices[1] = Vertex2D{matrix * Vector2(size.x + offset.x, offset.y), Vector2(botright.x, topleft.y), modulate};
        Vertices[2] = Vertex2D{matrix * Vector2(size.x + offset.x, size.y + offset.y), botright, modulate};
        Vertices[3] = Vertex2D{matrix * Vector2(offset.x, size.y + offset.y), Vector2(topleft.x, botright.y), modulate};
    }

} // namespace ASEngine
