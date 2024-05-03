
#ifndef ASENGINE_VECTOR3_H
#define ASENGINE_VECTOR3_H

#include "Core/Error/Assertion.h"
#include "Math.h"

namespace ASEngine 
{

    struct Vector3 
    {
        //data
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;

        // constructors
        constexpr Vector3() = default;
        constexpr Vector3(float _x, float _y, float _z): x(_x), y(_y), z(_z)
        {
        }
        constexpr Vector3(const Vector3 &v) = default;

        // consts

        // define constants
        static constexpr Vector3 ZERO()
        {
            return Vector3{0.0f, 0.0f, 0.0f};
        } 
        static constexpr Vector3 ONE()
        {
            return Vector3{1.0f, 1.0f, 0.0f};
        }
        static constexpr Vector3 LEFT()
        {
            return Vector3{-1.0f, 0.0f, 0.0f};
        }
        static constexpr Vector3 RIGHT()
        {
            return Vector3{1.0f, 0.0f, 0.0f};
        }
        static constexpr Vector3 DOWN()
        {
            return Vector3{0.0f, 1.0f, 0.0f};
        }
        static constexpr Vector3 UP()
        {
            return Vector3{0.0f, -1.0f, 0.0f};
        }
        static constexpr Vector3 FORWARD()
        {
            return Vector3{0.0f, 0.0f, 1.0f};
        }
        static constexpr Vector3 BACKWARD()
        {
            return Vector3{0.0f, 0.0f, -1.0f};
        }


        // dot product
        inline constexpr float Dot(const Vector3& v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        // lenghts
        inline float Length() const
        {
            return Math::Sqrt(x * x + y * y + z * z);
        }

        // length squared
        inline constexpr float LengthSquared() const
        {
            return x * x + y * y + z * z;
        }

        // abs x and y
        inline Vector3 Abs() const
        {
            return Vector3{
                Math::Abs(x),
                Math::Abs(y),
                Math::Abs(z)
            };
        }
        
        // normalized
        inline Vector3 Normalized() const
        {
            float length = this->Length();
            ASENGINE_ASSERT(length != 0.0f, "Cannot normalize Vector with length 0");
            return Vector3{x / length, y / length, z / length};
        };

        //add
        inline Vector3 &operator+=(const Vector3 &v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        friend inline constexpr Vector3 operator+(const Vector3 &a, const Vector3 &b)
        {
            return Vector3
            {
                a.x + b.x,
                a.y + b.y,
                a.z + b.z
            };
        }

        // sub
        inline Vector3 &operator-=(const Vector3 &v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        // sub
        friend inline constexpr Vector3 operator-(const Vector3 &a, const Vector3 &b)
        {
            return Vector3
            {
                a.x - b.x,
                a.y - b.y,
                a.z - b.z
            };
        }

        // scale
        inline Vector3 &operator*=(float s)
        {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        // scale
        friend inline constexpr Vector3 operator*(const Vector3 &a, float s)
        {
            return Vector3
            {
                a.x * s,
                a.y * s,
                a.z * s
            };
        }
        

        //multiply
        inline Vector3 &operator*=(const Vector3 &v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }

        friend inline Vector3 operator*(const Vector3 &a, const Vector3 &b)
        {
            return Vector3
            {
                a.x * b.x,
                a.y * b.y,
                a.z * b.z
            };
        }

        // division
        friend inline Vector3 operator/(const Vector3 &a, const Vector3 &b)
        {
            ASENGINE_ASSERT(b.x != 0.0f && b.y != 0.0f && b.z != 0.0f, "Cannot divide by 0");
            return Vector3
            {
                a.x / b.x,
                a.y / b.y,
                a.z / b.z
            };
        }

        //scale divistion
        friend inline Vector3 operator/(const Vector3 &a, float s)
        {
            ASENGINE_ASSERT(s != 0.0f, "Cannot divide by 0");
            return Vector3
            {
                a.x / s,
                a.y / s,
                a.z / s
            };
        }
    };

} // ASEngine

#endif //ASENGINE_VECTOR3_H
