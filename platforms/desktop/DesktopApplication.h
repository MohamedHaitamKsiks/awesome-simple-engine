#ifndef __ASENGINE_DESKTOP_APPLICATION_H
#define __ASENGINE_DESKTOP_APPLICATION_H


#include <sstream>
#include <iostream>
#include <chrono>
#define SEC_TO_MICRO 1000000.0f;

#include "ASEngine.h"
#include "GLFW/glfw3.h"

namespace ASEngine
{

    class DesktopApplication 
    {
    public:
        int Run();

    private:

        //glfw window
        GLFWwindow *m_Window = nullptr;

        // asengine application
        Application m_Application{};

        // window information
        struct
        {
            int Width = -1;
            int Height = -1;
            int XPos = 0;
            int YPos = 0;
        } m_WindowInfo;


        // mouse current position
        static vec2 s_MousePosition;

        // create window for desktop application
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
        void OnWindowSetTitle(const std::string& title);

        // on keyboard press
        static void OnKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods);

        // on mouse button
        static void OnMouseButton(GLFWwindow *window, int button, int action, int mods);

        // on mouse move
        static void OnMouseMove(GLFWwindow *window, double xpos, double ypos);
    };
    
} // namespace ASEngine

#endif