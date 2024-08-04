#ifndef __ASENGINE_INTERPOLATION_H
#define __ASENGINE_INTERPOLATION_H

#include "Macros/Foreach.h"

#define __ASENGINE_DEFINE_INTERPOLATION_FLOAT_EASE_FUNCTION(funcName) \
static float Float ## funcName ## EaseIn(float t); \
static float Float ## funcName ## EaseOut(float t); \
static float Float ## funcName ## EaseInOut(float t);

#define __ASENGINE_DEFINE_INTERPOLATION_FLOAT_EASE_FUNCTIONS(...) FOREACH(__ASENGINE_DEFINE_INTERPOLATION_FLOAT_EASE_FUNCTION,  __VA_ARGS__)

#define __ASENGINE_DEFINE_INTERPOLATION_EASE_FUNCTION(funcName) \
template<typename T> \
static inline T funcName(const T& a, const T& b, float t) \
{ \
    return Linear(a, b, Float ## funcName(t)); \
}

#define __ASENGINE_DEFINE_INTERPOLATION_FUNCTION(funcName) \
__ASENGINE_DEFINE_INTERPOLATION_EASE_FUNCTION(funcName ## EaseIn) \
__ASENGINE_DEFINE_INTERPOLATION_EASE_FUNCTION(funcName ## EaseOut) \
__ASENGINE_DEFINE_INTERPOLATION_EASE_FUNCTION(funcName ## EaseInOut);

#define __ASENGINE_DEFINE_INTERPOLATION_FUNCTIONS(...) FOREACH(__ASENGINE_DEFINE_INTERPOLATION_FUNCTION,  __VA_ARGS__)

namespace ASEngine
{
    class Interpolation
    {
    public:
        template<typename T>
        static T Linear(const T& a, const T& b, float t)
        {
            return a + (b - a) * t;
        }

        template<typename T>
        static T LinearClamp(const T& a, const T& b, float t)
        {
            if (t < 0.0f)
                return a;
            else if (t > 1.0f)
                return b;

            return a + (b - a) * t;
        }

        __ASENGINE_DEFINE_INTERPOLATION_FUNCTIONS(
            Quad,
            Cubic,
            Exp,
            Back,
            Elastic
        );

    private:
        __ASENGINE_DEFINE_INTERPOLATION_FLOAT_EASE_FUNCTIONS(
            Quad,
            Cubic,
            Exp,
            Back,
            Elastic
        );
    };
} // namespace ASEngine

#endif // __ASENGINE_INTERPOLATION_H
