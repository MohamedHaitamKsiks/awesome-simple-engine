
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
        inline vec2 operator+(vec2 v) {
            return vec2
            {
                x + v.x,
                y + v.y
            };
        }

        //sub
        inline vec2 operator-(vec2 v) {
            return vec2
            {
                x - v.x,
                y - v.y
            };
        }

        //scale
        inline vec2 operator*(float s) {
            return vec2
            {
                x * s,
                y * s
            };
        }

        //multiply
        inline vec2 operator*(vec2 v) {
            return vec2
            {
                x * v.x,
                y * v.y
            };
        }

        //scale
        inline vec2 operator/(float s) {
            return vec2
            {
                x / s,
                y / s
            };
        }

        //equal
        inline bool operator==(vec2 v) {
            return x == v.x && y == v.y;
        }

    };

} // ASEngine

#endif //ASENGINE_VEC2_H
