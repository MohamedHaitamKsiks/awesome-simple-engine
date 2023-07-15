#include "mat3.h"

namespace ASEngine
{
    mat3 mat3::scale(const vec2& s)
    {
        mat3 b = {{s.x, 0.0f, 0.0f,
                   0.0f, s.y, 0.0f,
                   0.0f, 0.0f, 1.0f}};
        return b;
    }

    mat3 mat3::rotation(float angle)
    {
        mat3 b = {{cos(angle), sin(angle), 0.0f,
                   -sin(angle), cos(angle), 0.0f,
                   0.0f, 0.0f, 1.0f}};
        return b;
    }

    mat3 mat3::translate(const vec2& v)
    {
        mat3 b = {{1.0f, 0.0f, v.x,
                   0.0f, 1.0f, v.y,
                   0.0f, 0.0f, 1.0f}};
        return b;
    }

    mat3 mat3::transform(const vec2& translate, const vec2& scale, float rotation)
    {
        mat3 b = {{scale.x * cos(rotation), scale.y * sin(rotation), translate.x,
                   -scale.x * sin(rotation), scale.y * cos(rotation), translate.y,
                   0.0f, 0.0f, 1.0f}};
        return b;
    }

    std::string mat3::toString()
    {
        std::ostringstream ss;

        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < 3; i++)
                ss << (*this)[j][i] << ",";
            
        }
        return ss.str();
    }
} // namespace ASEngine
