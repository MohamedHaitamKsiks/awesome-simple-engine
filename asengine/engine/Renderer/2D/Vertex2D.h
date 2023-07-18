#ifndef ASENGINE_VERTEX2D_H
#define ASENGINE_VERTEX2D_H

#include "engine/Renderer/GraphicsAPI.h"
#include "engine/Renderer/Color.h"

#include "engine/Math/vec2.h"

#include <cstddef>

namespace ASEngine
{

    struct Vertex2D
    {
        // vertex data
        vec2 Position = vec2::ZERO();
        vec2 UV = vec2::ZERO();
        Color Modulate = Color::WHITE();
    };

} // ASEngine

#endif // ASENGINE_VERTEX2D_H
