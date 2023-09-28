#ifndef ASENGINE_CAMERA_2D_H
#define ASENGINE_CAMERA_2D_H

#include "Core/Math/vec2.h"

namespace ASEngine
{
    struct Camera2D
    {
        // camera position
        vec2 Position = vec2::ZERO();

        // camera rotation
        float Rotation = 0.0f;

        // camera zoom
        float Zoom = 1.0f;

    };
} // namespace ASEngine


#endif // ASENGINE_CAMERA_2D_H