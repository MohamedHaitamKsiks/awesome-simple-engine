#ifndef __ASENGINE_MATH_H
#define __ASENGINE_MATH_H

#include <cmath>


namespace ASEngine
{
    // interface for cmath functions
    class  Math
    {
    public:
        // constants
        static constexpr float PI = M_PI;
        static constexpr float E = M_E;

        // functions 
        static inline float Cos(float x)
        {
            return cosf(x);
        }

        static inline float Sin(float x)
        {
            return sinf(x);
        }

        static inline float Tan(float x)
        {
            return tanf(x);
        }

        static inline float Sqrt(float x)
        {
            return sqrtf(x);
        }

        static inline float Pow(float x, float n)
        {
            return powf(x, n);
        }

        static inline float Acos(float x)
        {
            return acosf(x);
        }

        static inline float Asin(float x)
        {
            return asinf(x);
        }

        static inline float Atan(float x)
        {
            return atanf(x);
        }

        static inline float Atan2(float y, float x)
        {
            return atan2f(y, x);
        }

        static inline float Exp(float x)
        {
            return expf(x);
        }

        static inline float Log(float x)
        {
            return logf(x);
        }

        template <typename T>
        static constexpr inline T Abs(T x)
        {
            return (x < static_cast<T>(0)) ? -x: x;
        }

        template <typename T>
        static inline constexpr T Sign(T x)
        {
            if (x > static_cast<T>(0))
                return static_cast<T>(1);
            else if (x < static_cast<T>(0))
                return static_cast<T>(-1);
            else
                return static_cast<T>(0);
        }

        template <typename T>
        static inline constexpr const T &Max(const T &a, const T &b)
        {
            return (a > b)? a: b;
        }

        template <typename T>
        static inline constexpr const T &Min(const T &a, const T &b)
        {
            return (a < b) ? a : b;
        }
    };
} // namespace ASEngine

#endif // __ASENGINE_MATH_H