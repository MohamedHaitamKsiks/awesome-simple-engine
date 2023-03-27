//
// Created by ksiks_wa3r on 3/21/23.
//

#ifndef MY_APPLICATION_COLOR_H
#define MY_APPLICATION_COLOR_H

namespace ASEngine {

    struct Color {
        //rgba
        float r;
        float g;
        float b;
        float a;

        //colors
        static Color white;
        static Color red;
        static Color blue;
        static Color green;
        static Color black;
        static Color transparent;
    };


} //ASEngine

#endif //MY_APPLICATION_COLOR_H
