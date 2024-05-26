
#ifndef __ASENGINE_VEC2_H
#define __ASENGINE_VEC2_H

#include "Math.h"
#include "Core/Error/Assertion.h"

namespace ASEngine 
{
    
    // 2D Vector
    struct Vector2 
    {
                
        // data
        float x = 0.0f;
        float y = 0.0f;

        // constructors
        constexpr Vector2() = default;
        constexpr Vector2(float _x, float _y): x(_x), y(_y)
        {
        }
        constexpr Vector2(const Vector2& v) = default;

        // Vector2 Constants
        static inline constexpr Vector2 ZERO() 
        {
            return Vector2{0.0f, 0.0f};
        }
        static inline constexpr Vector2 ONE()
        {
            return Vector2{1.0f, 1.0f};
        }
        static inline constexpr Vector2 LEFT()
        {
            return Vector2{-1.0f, 0.0f};
        }
        static inline constexpr Vector2 RIGHT()
        {
            return Vector2{1.0f, 0.0f};
        }
        static inline constexpr Vector2 DOWN()
        {
            return Vector2{0.0f, 1.0f};
        }
        static inline constexpr Vector2 UP()
        {
            return Vector2{0.0f, -1.0f};
        }

        // angle
        inline float Angle() const
        {
            return Math::Atan2(y, x);
        }

        // dot product
        inline constexpr float Dot(const Vector2 &v) const
        {
            return x * v.x + y * v.y;
        }

        // lenghts
        inline float Length() const
        {
            return Math::Sqrt(x * x + y * y);
        }

        // length squared
        inline constexpr float LengthSquared() const
        {
            return x * x + y * y;
        }

        // abs x and y
        inline constexpr Vector2 Abs() const
        {
            return Vector2
            {
                Math::Abs(x),
                Math::Abs(y)
            };
        }

        // rotate around z axis
        Vector2 Rotate(float angle) const;

        // normalized
        inline Vector2 Normalize() const
        {
            float length = this->Length();
            ASENGINE_ASSERT(length != 0.0f, "Cannot normalize Vector with length 0");
            return Vector2{x / length, y / length};
        }


        //add
        inline Vector2& operator+=(const Vector2& v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        friend inline constexpr Vector2 operator+(const Vector2 &a, const Vector2 &b)
        {
            return Vector2
            {
                a.x + b.x,
                a.y + b.y
            };
        }

        //sub
        inline Vector2 &operator-=(const Vector2 &v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }

        friend inline constexpr Vector2 operator-(const Vector2 &a, const Vector2 &b)
        {
            return Vector2
            {
                a.x - b.x,
                a.y - b.y
            };
        }

        //scale
        inline Vector2& operator*=(float s)
        {
            x *= s;
            y *= s;
            return *this;
        }

        friend inline constexpr Vector2 operator*(const Vector2 &a, float s)
        {
            return Vector2
            {
                a.x * s,
                a.y * s
            };
        }
        
        //multiply
        inline Vector2& operator*=(const Vector2& v)
        {
            x *= v.x;
            y *= v.y;
            return *this;
        }

        friend inline constexpr Vector2 operator*(const Vector2 &a, const Vector2 &b)
        {
            return Vector2 
            {
                a.x * b.x,
                a.y * b.y
            };
        }

        // divide
        inline Vector2 &operator/=(const Vector2 &v)
        {
            x /= v.x;
            y /= v.y;
            return *this;
        }

        friend inline constexpr Vector2 operator/(const Vector2 &a, const Vector2 &b)
        {
            return Vector2 
            {
                a.x / b.x,
                a.y / b.y
            };
        }

        //divide scaled
        inline Vector2 &operator/=(float s)
        {
            x /= s;
            y /= s;
            return *this;
        }

        friend inline constexpr Vector2 operator/(const Vector2 &a, float s)
        {
            return Vector2 
            {
                a.x / s,
                a.y / s
            };
        }


        //equal
        friend inline constexpr bool operator==(const Vector2 &a, const Vector2 &b)
        {
            return a.x == b.x && a.y == b.y;
        }
        
    };



} // ASEngine

#endif //ASENGINE_VEC2_H
