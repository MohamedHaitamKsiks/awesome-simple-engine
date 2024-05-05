#ifndef ASENGINE_COLOR_H
#define ASENGINE_COLOR_H

namespace ASEngine {

    struct Color {
        //rgba
        float r = 0.0f;
        float g = 0.0f;
        float b = 0.0f;
        float a = 0.0f;

        inline bool operator==(Color c){
            return r == c.r && g == c.g && b == c.b && a == c.a;
        }

        inline Color operator*(float s) {
            return Color{
                r * s,
                g * s,
                b * s,
                a * s
            };
        }

        inline Color operator+(Color c) {
            return Color{
                r + c.r,
                g + c.g,
                b + c.b,
                a + c.a
            };
        }

        //colors

        // white
        static constexpr Color WHITE()
        {
            return Color{1.0f, 1.0f, 1.0f, 1.0f};
        };

        // red
        static constexpr Color RED()
        {
            return Color{1.0f, 0.0f, 0.0f, 1.0f};
        };

        // blue
        static constexpr Color BLUE()
        {
            return Color{0.0f, 0.0f, 1.0f, 1.0f};
        };

        // green
        static constexpr Color GREEN()
        {
            return Color{0.0f, 1.0f, 0.0f, 1.0f};
        };

        // black
        static constexpr Color BLACK()
        {
            return Color{0.0f, 0.0f, 0.0f, 1.0f};
        };

        // transparent
        static constexpr Color TRANSPARENT()
        {
            return Color{0.0f, 0.0f, 0.0f, 0.0f};
        };
    };


} //ASEngine

#endif //ASENGINE_COLOR_H
