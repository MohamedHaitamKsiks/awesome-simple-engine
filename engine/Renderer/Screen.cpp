//
// Created by ksiks_wa3r on 3/20/23.
//

#include "Screen.h"

namespace ASEngine {

    void Screen::setSize(int _width, int _height) {
        Screen::width = _width;
        Screen::height = _height;
    }

    int Screen::getWidth() {
        return Screen::width;
    }

    int Screen::getHeight() {
        return Screen::height;
    }

    mat3 Screen::getView() {
        mat3 view = mat3{{
            2.0f / Screen::width, 0.0f, -1.0f,
            0.0f, -2.0f / Screen::height, 1.0f,
            0.0f, 0.0f, 1.0f
        }};
        return view;
    }

    int Screen::width = 270;
    int Screen::height = 480;

    int Screen::windowWidth = -1;
    int Screen::windowHeight = -1;

    vec2 Screen::getSize() {
        return vec2{(float)width, (float)height};
    }

    vec2 Screen::getCenter() {
        return Screen::getSize() * 0.5f ;
    }

    void Screen::setWindowSize(int _width, int _height) {
        Screen::windowWidth = _width;
        Screen::windowHeight = _height;
    }

    int Screen::getWindowWidth() {
        return Screen::windowWidth;
    }

    int Screen::getWindowHeight() {
        return Screen::windowHeight;
    }

} // ASEngine