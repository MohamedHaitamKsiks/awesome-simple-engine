#include "vec2.h"

namespace ASEngine
{

    float vec2::angle()
    {
        return atan2(y, x);
    }

    // dot product
    float vec2::dot(const vec2& v)
    {
        return x * v.x + y * v.y;
    }

    // lenghts
    float vec2::length()
    {
        return sqrtf(x * x + y * y);
    }

    // length squared
    float vec2::lengthSquared()
    {
        return x * x + y * y;
    }

    // rotate
    vec2 vec2::rotate(float angle)
    {
        return vec2
        {
            x *cos(angle) - y *sin(angle),
            x * sin(angle) + y * cos(angle)
        };
    }

    // normalized
    vec2 vec2::normalized()
    {
        return *this / this->length();
    }
} // namespace ASEngine
