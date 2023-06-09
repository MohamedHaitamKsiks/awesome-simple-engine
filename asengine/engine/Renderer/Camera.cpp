//
// Created by ksiks_wa3r on 3/21/23.
//

#include "Camera.h"

namespace ASEngine {

    mat3 Camera::getMatrix() {
        return mat3::translate(position * -1.0f) * mat3::scale(vec2::one() * zoom);
    }

    Camera* Camera::current = nullptr;
} // ASEngine