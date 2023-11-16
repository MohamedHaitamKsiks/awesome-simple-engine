#ifndef ASENGINE_CAMERA_3D_H
#define ASENGINE_CAMERA_3D_H

#include "Core/Math/vec3.h"

namespace ASEngine
{
    struct Camera3D
    {
        // camera position
        vec3 Position = vec3::ZERO();

        // projection data

        // near plane
        float Near = 0.05f;

        // far plane
        float Far = 4000.0f;

        // field of view in rads
        float FOV = 5.0f * M_PI / 16.0f;
    };
} // namespace ASEngine

#endif // ASENGINE_CAMERA_3D_H