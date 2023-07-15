
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
        float angle();

        // dot product
        float dot(const vec2& v);

        // lenghts
        float length();

        // length squared
        float lengthSquared();

        // rotate
        vec2 rotate(float angle);

        // normalized
        vec2 normalized();

        //add
        inline vec2 operator+(const vec2& v) {
            return vec2
            {
                x + v.x,
                y + v.y
            };
        }

        //sub
        inline vec2 operator-(const vec2& v) {
            vec2 out{};
            out.x = x - v.x;
            out.y = y - v.y;
            return out;
        }

        //scale
        inline vec2 operator*(float s) {
            vec2 out{};
            out.x = x * s;
            out.y = y * s;
            return out;
        }

        //multiply
        inline vec2 operator*(const vec2& v) {
            vec2 out{};
            out.x = x * v.x;
            out.y = y * v.y;
            return out;
        }

        //scale
        inline vec2 operator/(float s) {
            vec2 out{};
            out.x = x / s;
            out.y = y / s;
            return out;
        }

        //equal
        inline bool operator==(const vec2& v) {
            return x == v.x && y == v.y;
        }

    };

} // ASEngine

#endif //ASENGINE_VEC2_H
