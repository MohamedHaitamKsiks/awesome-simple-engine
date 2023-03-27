//
// Created by ksiks_wa3r on 3/1/23.
//

#ifndef MY_APPLICATION_VEC2_H
#define MY_APPLICATION_VEC2_H

#include "math.h"

namespace ASEngine {

    struct vec2 {
        float x;
        float y;
        //add
        inline vec2 operator+(vec2 v) {
            vec2 out{};
            out.x = x + v.x;
            out.y = y + v.y;
            return out;
        }

        //sub
        inline vec2 operator-(vec2 v) {
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

        //scale
        inline vec2 operator/(float s) {
            vec2 out{};
            out.x = x / s;
            out.y = y / s;
            return out;
        }

        //angle
        float angle() {
            return atan2(y, x);
        }

        //dot product
        float dot(vec2 v) {
            return  x * v.x + y * v.y;
        }

        //lenghts
        float length() {
            return sqrtf( x * x + y * y );
        }

        //length squared
        float lengthSquared() {
            return x * x + y * y;
        }

        //rotate
        vec2 rotate( float angle) {
            vec2 out{};
            out.x = x * cos(angle) - y * sin(angle);
            out.y = x * sin(angle) + y * cos(angle);
            return out;
        }

        //normalized
        vec2 normalized() {
            if (length() == 0.0f)
                return zero();

            vec2 out{};
            out.x = x / length();
            out.y = y / length();
            return out;
        }

        //consts
        static vec2 zero() {
            return vec2{0.0f, 0.0f};
        }

        static vec2 one() {
            return vec2{1.0f, 1.0f};
        }

    };

} // ASEngine

#endif //MY_APPLICATION_VEC2_H
