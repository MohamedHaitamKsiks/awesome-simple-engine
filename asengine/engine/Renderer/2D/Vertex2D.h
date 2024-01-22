#ifndef ASENGINE_VERTEX2D_H
#define ASENGINE_VERTEX2D_H

#include "Renderer/GraphicsAPI.h"
#include "Renderer/Color.h"
#include "Renderer/VertexInput.h"

#include "Core/Math/vec2.h"

#include <cstddef>

namespace ASEngine
{

    struct Vertex2D
    {
        // vertex data
        vec2 Position = vec2::ZERO();
        vec2 UV = vec2::ZERO();
        Color Modulate = Color::WHITE();

        static VertexInputLayout GetVertexInputLayout();
    };

} // ASEngine

#endif // ASENGINE_VERTEX2D_H
