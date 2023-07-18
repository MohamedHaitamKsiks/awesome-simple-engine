#ifndef ASENGINE_CAMERA_2D_H
#define ASENGINE_CAMERA_2D_H

#include "engine/Math/vec2.h"

namespace ASEngine
{
    class Camera2D
    {
    public:
        // camera position
        vec2 position = vec2::ZERO();

        // camera offset 
        vec2 offset = vec2::ZERO();

        // camera rotation
        float rotation = 0.0f;

        // camera zoom
        float zoom = 1.0f;

        

    };
} // namespace ASEngine


#endif // ASENGINE_CAMERA_2D_H