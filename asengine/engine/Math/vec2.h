
#ifndef ASENGINE_VEC2_H
#define ASENGINE_VEC2_H

#include "math.h"

namespace ASEngine {

    struct vec2 {
        //data
        float x = 0.0f;
        float y = 0.0f;

        // consts

        // vector (0, 0)
        static constexpr vec2 ZERO()
        {
            return {0.0f, 0.0f}; 
        };
        // vector (1, 1)
        static constexpr vec2 ONE()
        {
            return {1.0f, 1.0f};
        };
        // vector(-1, 0)
        static constexpr vec2 LEFT()
        {
            return {-1.0f, 0.0f};
        };
        // vector(1, 0)
        static constexpr vec2 RIGHT()
        {
            return {1.0f, 0.0f};
        };
        // vector(0, -1)
        static constexpr vec2 UP()
        {
            return {0.0f, -1.0f};
        };
        // vector(0, 1)
        static constexpr vec2 DOWN()
        {
            return {0.0f, 1.0f};
        };


        // angle
        float Angle();

        // dot product
        float Dot(const vec2& v);

        // lenghts
        float Length();

        // length squared
        float LengthSquared();

        // rotate
        vec2 Rotate(float angle);

        // normalized
        vec2 Normalized();

        //add
        friend inline vec2 operator+(const vec2 &a, const vec2 &b)
        {
            return vec2
            {
                a.x + b.x,
                a.y + b.y
            };
        }

        //sub
        friend inline vec2 operator-(const vec2 &a, const vec2 &b)
        {
            return vec2
            {
                a.x - b.x,
                a.y - b.y
            };
        }

        //scale
        friend inline vec2 operator*(const vec2 &a, float s)
        {
            return vec2
            {
                a.x * s,
                a.y * s
            };
        }
        
        //multiply
        friend inline vec2 operator*(const vec2 &a, const vec2 &b)
        {
            return vec2
            {
                a.x * b.x,
                a.y * b.y
            };
        }

        //scale
        friend inline vec2 operator/(const vec2 &a, float s)
        {
            return vec2
            {
                a.x / s,
                a.y / s
            };
        }

        //equal
        friend inline bool operator==(const vec2 &a, const vec2 &b)
        {
            return a.x == b.x && a.y == b.y;
        }
    };

} // ASEngine

#endif //ASENGINE_VEC2_H
