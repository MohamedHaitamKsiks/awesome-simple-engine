#ifndef ASENGINE_DESKTOP_APPLICATION_H
#define ASENGINE_DESKTOP_APPLICATION_H


#include "engine/asengine.h"

#include <sstream>
#include <iostream>
#include <chrono>
#define SEC_TO_MICRO 1000000.0f;

#include "GLFW/glfw3.h"

using namespace ASEngine;

class DesktopApplication 
{
public:
    void Start();

private:

    //glfw window
    GLFWwindow *m_Window = nullptr;

    // window information
    struct
    {
        int Width = -1;
        int Height = -1;
        int XPos = 0;
        int YPos = 0;
    } m_WindowInfo;

    //init desktop application
    bool Init();

    //update desktop application
    void Update(float delta);

    //derminate desktop application
    void Terminate();

    // on window resize
    void OnWindowChangeSize(int width, int height);
    
    // on window set fullscreen
    void OnWindowSetFullscreen(bool fullscreen);

    // on window set title
    void OnWindowSetTitle(std::string title);

    // on keyboard press
    static void OnKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
};

#endif