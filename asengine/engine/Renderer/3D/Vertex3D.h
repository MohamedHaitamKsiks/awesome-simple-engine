#ifndef ASENGINE_VERTEX3D_H
#define ASENGINE_VERTEX3D_H

#include "Renderer/GraphicsAPI.h"
#include "Renderer/Color.h"

#include "Core/Math/vec3.h"
#include "Core/Math/vec2.h"

#include "Renderer/VertexInput.h"

#include <cstddef>

namespace ASEngine
{
    struct Vertex3D
    {
        // vertex data
        vec3 Position = vec3::ZERO();
        vec3 Normal = vec3::ZERO();
        vec2 UV = vec2::ZERO();
        Color Modulate = Color::WHITE();

        static VertexInputLayout GetVertexInputLayout();
    };

} // ASEngine

#endif // ASENGINE_VERTEX3D_H
