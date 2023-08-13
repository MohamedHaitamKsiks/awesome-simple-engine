#include "vec2.h"

namespace ASEngine
{

    // rotate
    vec2 vec2::Rotate(float angle)
    {
        float cosAngle = cos(angle);
        float sinAngle = sin(angle);

        return vec2
        {
            x * cosAngle - y * sinAngle,
            x * sinAngle + y * cosAngle
        };
    }

} // namespace ASEngine
