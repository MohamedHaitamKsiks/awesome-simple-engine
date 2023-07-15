#ifndef ASENGINE_DESKTOP_APPLICATION_H
#define ASENGINE_DESKTOP_APPLICATION_H


#include "engine/asengine.h"

#include <sstream>
#include <iostream>
#include <chrono>
#define SEC_TO_MICRO 1000000.0f;

#include "GLFW/glfw3.h"

class DesktopApplication {
    public:
        void start();
    
    private:
        //singleton
        DesktopApplication* application = nullptr;

        //glfw window
        GLFWwindow *window;

        //init desktop application
        bool init();

        //update desktop application
        void update(float delta);

        //derminate desktop application
        void terminate();
};

#endif