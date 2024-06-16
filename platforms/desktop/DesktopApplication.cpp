#include "DesktopApplication.h"

namespace ASEngine
{

    int DesktopApplication::Run()
    {
        // init window
        if (!Init())
        {
            Debug::Error("Application coudn't started!");
            return 1;
        }

        // start gameloop
        // delta
        float delta = 0.01f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(m_Window))
        {
            // get time now
            const auto pastTime = std::chrono::high_resolution_clock::now();

            Update(delta);

            // compute delta
            const auto currentTime = std::chrono::high_resolution_clock::now();
            delta = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count() / SEC_TO_MICRO;
        }
        
        Terminate();
        return 0;
    }

    bool DesktopApplication::Init()
    {
        /* Initialize the library */
        if (!glfwInit())
            return false;

        // setup application modules and systems
        m_ASEngine.Setup();

        /* Create a windowed mode window and with no context */
        //
        m_Window = glfwCreateWindow(640, 480, "ASEngine Desktop Application", NULL, NULL);
        if (!m_Window)
        {
            Terminate();
            return false;
        }

        // center window
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);

        m_WindowInfo.XPos = (mode->width - 640) / 2;
        m_WindowInfo.YPos = (mode->height - 480) / 2;
        glfwSetWindowPos(m_Window, m_WindowInfo.XPos, m_WindowInfo.YPos);

        // set window to not resizable
        glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, GLFW_FALSE);

        // init asengine systems
        m_ASEngine.Init();

        /* listen to keyboard events */
        glfwSetKeyCallback(m_Window, DesktopApplication::OnKeyboard);

        /* listen on mouse */
        glfwSetCursorPosCallback(m_Window, OnMouseMove);
        glfwSetMouseButtonCallback(m_Window, OnMouseButton);

        // connect window signals   
        // Window &window = Window::GetInstance();
        // window.GetResizeSignal().Connect(std::bind(&DesktopApplication::OnWindowChangeSize, this, std::placeholders::_1, std::placeholders::_2));
        // window.GetTitleSignal().Connect(std::bind(&DesktopApplication::OnWindowSetTitle, this, std::placeholders::_1));
        // window.GetFullscreenSignal().Connect(std::bind(&DesktopApplication::OnWindowSetFullscreen, this, std::placeholders::_1));

        return true;
    }


    void DesktopApplication::Update(float delta)
    {
        // update app
        m_ASEngine.Update(delta);

        /* Poll for and process events */
        glfwPollEvents();
    }

    void DesktopApplication::Terminate()
    {
        m_ASEngine.Terminate();
        glfwTerminate();
    }

    void DesktopApplication::OnWindowChangeSize(int width, int height)
    {
        glfwSetWindowSize(m_Window, width, height);
        m_WindowInfo.Width = width;
        m_WindowInfo.Height = height;
    }

    void DesktopApplication::OnWindowSetFullscreen(bool fullscreen)
    {
        if (fullscreen)
        {
            // save window size
            int width, height;
            glfwGetWindowSize(m_Window, &width, &height);
            glfwGetWindowPos(m_Window, &m_WindowInfo.XPos, &m_WindowInfo.YPos);

            // set full screen
            GLFWmonitor *monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode *mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            glfwSetWindowSize(m_Window, mode->width, mode->height);

            // set size
            // Window::GetInstance().SetSize(mode->width, mode->height);
            m_WindowInfo.Width = width;
            m_WindowInfo.Height = height;
        }
        else 
        {
            // set windowed
            glfwSetWindowMonitor(m_Window, NULL, m_WindowInfo.XPos, m_WindowInfo.YPos, m_WindowInfo.Width, m_WindowInfo.Height, 0);
            // Window::SetSize(m_WindowInfo.Width, m_WindowInfo.Height);
        }
    }

    void DesktopApplication::OnWindowSetTitle(const std::string& title)
    {
        glfwSetWindowTitle(m_Window, title.c_str());
    }

    void DesktopApplication::OnKeyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (action != GLFW_PRESS && action != GLFW_RELEASE)
            return;

        // bake keyboard event
        // InputEventKeyboard keyboardEvent;
        // keyboardEvent.Code = key;
        // keyboardEvent.Pressed = action == GLFW_PRESS;

        // InputEvent event{keyboardEvent};

        // push event to application event queue
        // Application::GetInstance().QueueInputEvent(event);
    }

    Vector2 DesktopApplication::s_MousePosition = Vector2::ZERO();

    void DesktopApplication::OnMouseButton(GLFWwindow *window, int button, int action, int mods)
    {
        // bake mouse button
        InputEventMouseButton mouseButtonEvent;
        mouseButtonEvent.Position = s_MousePosition;
        mouseButtonEvent.Button = (button == GLFW_MOUSE_BUTTON_LEFT) ? MouseButton::LEFT_CLICK: MouseButton::RIGHT_CLICK;
        mouseButtonEvent.Pressed = action == GLFW_PRESS;

        InputEvent event{mouseButtonEvent};

        // push event to application event queue
        // Application::GetInstance().QueueInputEvent(event);
    }

    void DesktopApplication::OnMouseMove(GLFWwindow *window, double xpos, double ypos)
    {
        // update mouse position
        s_MousePosition = Vector2{
            (float)xpos, 
            (float)ypos
        };

        // bake mouse mouve event
        // InputEventMouseMove mouseMoveEvent;
        // mouseMoveEvent.Position = s_MousePosition;

        // InputEvent event{mouseMoveEvent};

        // push event to application event queue
        // Application::GetInstance().QueueInputEvent(event);
    }
    
} // namespace ASEngine