#include "vec2.h"

namespace ASEngine
{

    float vec2::Angle()
    {
        return atan2(y, x);
    }

    // dot product
    float vec2::Dot(const vec2& v)
    {
        return x * v.x + y * v.y;
    }

    // lenghts
    float vec2::Length()
    {
        return sqrtf(x * x + y * y);
    }

    // length squared
    float vec2::LengthSquared()
    {
        return x * x + y * y;
    }

    // rotate
    vec2 vec2::Rotate(float angle)
    {
        return vec2
        {
            x *cos(angle) - y *sin(angle),
            x * sin(angle) + y * cos(angle)
        };
    }

    // normalized
    vec2 vec2::Normalized()
    {
        return *this / this->Length();
    }
} // namespace ASEngine
