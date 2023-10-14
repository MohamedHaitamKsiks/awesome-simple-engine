
#ifndef ASENGINE_VEC3_H
#define ASENGINE_VEC3_H

#include "math.h"

namespace ASEngine {

    struct vec3 {
        //data
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        // consts

        // vector (0, 0, 0)
        static constexpr vec3 ZERO()
        {
            return {0.0f, 0.0f, 0.0f}; 
        };
        // vector (1, 1, 1)
        static constexpr vec3 ONE()
        {
            return {1.0f, 1.0f, 1.0f};
        };
        // vector(-1, 0, 0)
        static constexpr vec3 LEFT()
        {
            return {-1.0f, 0.0f, 0.0f};
        };
        // vector(1, 0, 0)
        static constexpr vec3 RIGHT()
        {
            return {1.0f, 0.0f, 0.0f};
        };
        // vector(0, -1, 0)
        static constexpr vec3 UP()
        {
            return {0.0f, -1.0f, 0.0f};
        };
        // vector(0, 1, 0)
        static constexpr vec3 DOWN()
        {
            return {0.0f, 1.0f, 0.0f};
        };
        // vector(0, 0,  1)
        static constexpr vec3 FORWARD()
        {
            return {0.0f, 0.0f, 1.0f};
        };
        // vector(0, 0, 1)
        static constexpr vec3 BACKWARD()
        {
            return {0.0f, 0.0f,-1.0f};
        };

        // dot product
        inline float Dot(const vec3& v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        // lenghts
        inline float Length() const
        {
            return sqrtf(x * x + y * y + z * z);
        }

        // length squared
        inline float LengthSquared() const
        {
            return x * x + y * y + z * z;
        }

        // abs x and y
        inline vec3 Abs() const
        {
            return vec3
            {
                abs(x),
                abs(y),
                abs(z)
            };
        }
        
        // normalized
        inline vec3 Normalized() const
        {
            return (this->Length() > 0.0f) ? *this / this->Length() : vec3::ZERO();
        };

        //add
        friend inline vec3 operator+(const vec3 &a, const vec3 &b)
        {
            return vec3
            {
                a.x + b.x,
                a.y + b.y,
                a.z + b.z
            };
        }

        //sub
        friend inline vec3 operator-(const vec3 &a, const vec3 &b)
        {
            return vec3
            {
                a.x - b.x,
                a.y - b.y,
                a.z - b.z
            };
        }

        //scale
        friend inline vec3 operator*(const vec3 &a, float s)
        {
            return vec3
            {
                a.x * s,
                a.y * s,
                a.z * s
            };
        }
        
        //multiply
        friend inline vec3 operator*(const vec3 &a, const vec3 &b)
        {
            return vec3
            {
                a.x * b.x,
                a.y * b.y,
                a.z * b.z
            };
        }

        // multiply
        friend inline vec3 operator/(const vec3 &a, const vec3 &b)
        {
            return vec3
            {
                a.x / b.x,
                a.y / b.y,
                a.z / b.z
            };
        }

        //scale
        friend inline vec3 operator/(const vec3 &a, float s)
        {
            return vec3
            {
                a.x / s,
                a.y / s,
                a.z / s
            };
        }
    };

} // ASEngine

#endif //ASENGINE_VEC3_H
