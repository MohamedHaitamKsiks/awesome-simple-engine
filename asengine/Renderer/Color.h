#ifndef __ASENGINE_COLOR_H
#define __ASENGINE_COLOR_H

#include "API/API.h"

namespace ASEngine 
{

    struct ASENGINE_API Color
    {
        //red
        float r = 0.0f;
        
        // green
        float g = 0.0f;
        
        // blue
        float b = 0.0f;
        
        // alpha
        float a = 0.0f;

        constexpr Color() = default;
        constexpr Color(float _r, float _g, float _b, float _a = 1.0f): r(_r), g(_g), b(_b), a(_a)
        {
        }

        inline constexpr bool operator==(const Color& c){
            return r == c.r && g == c.g && b == c.b && a == c.a;
        }

        inline constexpr Color operator*(float s)
        {
            return Color{
                r * s,
                g * s,
                b * s,
                a * s
            };
        }

        inline constexpr Color operator+(const Color &c)
        {
            return Color{
                r + c.r,
                g + c.g,
                b + c.b,
                a + c.a
            };
        }

        //colors

        // white
        static inline constexpr Color WHITE()
        {
            return Color{1.0f, 1.0f, 1.0f, 1.0f};
        }

        // red
        static inline constexpr Color RED()
        {
            return Color{1.0f, 0.0f, 0.0f, 1.0f};
        }

        // blue
        static inline constexpr Color BLUE()
        {
            return Color{0.0f, 0.0f, 1.0f, 1.0f};
        }

        // green
        static inline constexpr Color GREEN()
        {
            return Color{0.0f, 1.0f, 0.0f, 1.0f};
        }

        // black
        static inline constexpr Color BLACK()
        {
            return Color{0.0f, 0.0f, 0.0f, 1.0f};
        }

        // transparent
        static inline constexpr Color TRANSPARENT()
        {
            return Color{0.0f, 0.0f, 0.0f, 0.0f};
        }
    };


} //ASEngine

#endif //ASENGINE_COLOR_H
