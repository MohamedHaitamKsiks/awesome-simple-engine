#ifndef __ASENGINE_QUAD_2D_H
#define __ASENGINE_QUAD_2D_H

#include "Vertex2D.h"

#include "Core/Math/Vector2.h"
#include "Core/Math/Matrix3x3.h"

#include "Renderer/Color.h"

#include "API/API.h"

namespace ASEngine
{
    // quad vertices
    struct ASENGINE_API Quad2D
    {
        Vertex2D Vertices[4];

        // create 1x1 white quad
        Quad2D() = default;

        // create widthxheight white quad
        Quad2D(const Vector2& size);

        // create width x height quad with color
        Quad2D(const Vector2 &size, const Color &modulate);

        // create width x height quad with color and matrix
        Quad2D(const Vector2& size, const Matrix3x3& matrix, const Color& modulate);

        //  create width x height quad with color and matrix and uv topleft - botright
        Quad2D(const Vector2 &size, const Matrix3x3 &matrix, const Color &modulate, const Vector2 &topleft, const Vector2 &botright);

        // craete quad with width x height and color and matrix and uv topleft - botright and offset ()
        void Create(const Vector2 &size, const Matrix3x3 &matrix, const Color &modulate, const Vector2 &topleft, const Vector2 &botright, const Vector2& offset = Vector2::ZERO());
    };
} // namespace ASEngine


#endif // __ASENGINE_QUAD_2D_H
