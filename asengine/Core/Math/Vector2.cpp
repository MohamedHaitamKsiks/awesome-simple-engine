#include "Vector2.h"

namespace ASEngine
{

    // rotate
    Vector2 Vector2::Rotate(float angle) const
    {
        float cosAngle = Math::Cos(angle);
        float sinAngle = Math::Sin(angle);

        return Vector2
        {
            x * cosAngle + y * sinAngle,
            -x * sinAngle + y * cosAngle
        };
    }

} // namespace ASEngine
