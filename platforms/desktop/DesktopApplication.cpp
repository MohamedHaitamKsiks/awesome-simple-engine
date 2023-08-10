#include "DesktopApplication.h"
#include "ecs/registry.h"

void DesktopApplication::Start()
{
    if (!Init())
    {
        Debug::Log("Application coudn't started!");
        return;
    }

    // start gameloop
    // delta
    float delta = 0.0f;
    float fps = 0.0f;
    float avgFps = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_Window))
    {
        // get time now
        auto pastTime = std::chrono::high_resolution_clock::now();

        Update(delta);
        if (delta > 0.0f)
        {
            std::stringstream ss;
            ss << 1.0f / delta << " FPS";
            Window::SetTitle(ss.str());
        }

        // compute delta
        auto currentTime = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count() / SEC_TO_MICRO;
    }

    Terminate();
}

bool DesktopApplication::Init()
{
    /* Initialize the library */
    if (!glfwInit())
        return false;

    /* Create a windowed mode window and its OpenGL context */
    //
    m_Window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
   
    if (!m_Window)
    {
        glfwTerminate();
        return false;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, GLFW_FALSE);

    // create asengine app
    Application::Create(Platform::DESKTOP);

    // connect window signals
    Window::ResizeSignal().Connect(std::bind(&DesktopApplication::OnWindowChangeSize, this, std::placeholders::_1, std::placeholders::_2));
    Window::TitleSignal().Connect(std::bind(&DesktopApplication::OnWindowSetTitle, this, std::placeholders::_1));
    Window::FullscreenSignal().Connect(std::bind(&DesktopApplication::OnWindowSetFullscreen, this, std::placeholders::_1));

    // ecs registry
    ECSRegistry();

    // load resources
    Application::InitResourceManagers();

    // load project settings
    Application::LoadProjectSettings();

    return true;
}

void DesktopApplication::Update(float delta)
{
    Application::Update(delta);
    /* Swap front and back buffers */
    glfwSwapBuffers(m_Window);
    /* Poll for and process events */
    glfwPollEvents();
}

void DesktopApplication::Terminate()
{
    glfwTerminate();
    Application::Terminate();
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
        // save window info
        glfwGetWindowSize(m_Window, &m_WindowInfo.Width, &m_WindowInfo.Height);
        // set full screen
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else 
    {
        // set windowed
        glfwSetWindowMonitor(m_Window, NULL, m_WindowInfo.XPos, m_WindowInfo.YPos, m_WindowInfo.Width, m_WindowInfo.Height, 0);
    }
}

void DesktopApplication::OnWindowSetTitle(std::string title)
{
    glfwSetWindowTitle(m_Window, title.c_str());
}