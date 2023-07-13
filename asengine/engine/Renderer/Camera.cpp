
#include "Camera.h"

namespace ASEngine 
{
    
    Camera* Camera::current = nullptr;

    mat3 Camera::getMatrix() 
    {
        return mat3::translate(position * -1.0f) * mat3::scale(vec2::one() * zoom);
    }

} // ASEngine