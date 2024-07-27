#include "DesktopDisplay.h"
#include "Core/ASEngine/ASEngine.h"

namespace ASEngine
{
    void DesktopDisplay::InitImp()
    {
        if (!glfwInit())
        {
            glfwTerminate();
            return;
        }

        // get settings
        const auto& displaySettings = ASEngine::GetInstance().GetSettings().Display;
        const auto& windowSettings = displaySettings.Window;
        const auto& renderingSettings = displaySettings.Rendering;
        const auto& applicationSettings = ASEngine::GetInstance().GetSettings().Application;

        // create window with default values
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        if (renderingSettings.Backend == Renderer::Backend::OPENGL)
        {
            // init opengl context
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        }
        else
        {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        }

        m_Window = glfwCreateWindow(windowSettings.Width, windowSettings.Height, applicationSettings.Name.c_str(), nullptr, nullptr);

        glfwMakeContextCurrent(m_Window);
        glfwSwapInterval(0);

        // set settings
        SetWindowSize(windowSettings.Width, windowSettings.Height);
        SetWindowTitle(applicationSettings.Name);
        SetFullscreen(windowSettings.Fullscreen);
        SetKeepAspectRatio(windowSettings.KeepAspectRatio);

        // set input callback
        glfwSetKeyCallback(m_Window, DesktopDisplay::GLFWKeyCallback);
        glfwSetCursorPosCallback(m_Window, DesktopDisplay::GLFWCursorPosCallback);
        glfwSetMouseButtonCallback(m_Window, DesktopDisplay::GLFWMouseButtonCallback);
    }

    void DesktopDisplay::TerminateImp()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void DesktopDisplay::SetWindowSizeImp(int width, int height)
    {
        // set size
        glfwSetWindowSize(m_Window, width, height);

        // set position to center
        if (!IsFullscreen())
        {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);

            m_PositionX = (mode->width - width) / 2;
            m_PositionY = (mode->height - height) / 2;
            glfwSetWindowPos(m_Window, m_PositionX, m_PositionY);
        }
    }

    void DesktopDisplay::SetWindowTitleImp(const std::string &title)
    {
        glfwSetWindowTitle(m_Window, title.c_str());
    }

    void DesktopDisplay::SetFullscreenImp(bool fullscreen)
    {
        if (!fullscreen)
        {
            // set windowed
            glfwSetWindowMonitor(m_Window, NULL, m_PositionX, m_PositionY, m_WindowedWindowWidth, m_WindowedWindowHeight, 0);
            SetWindowSize(m_WindowedWindowWidth, m_WindowedWindowHeight);
            return;
        }

        // save window size
        int width, height;
        int posX, posY;
        glfwGetWindowSize(m_Window, &width, &height);
        glfwGetWindowPos(m_Window, &posX, &posY);

        m_WindowedWindowWidth = static_cast<uint32_t>(width);
        m_WindowedWindowHeight = static_cast<uint32_t>(height);
        m_PositionX = static_cast<uint32_t>(posX);
        m_PositionY = static_cast<uint32_t>(posY);

        // set full screen
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(m_Window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        SetWindowSize(mode->width, mode->height);
    }

    void DesktopDisplay::BeginFrameImp()
    {
    }

    void DesktopDisplay::EndFrameImp()
    {
        glfwSwapBuffers(m_Window);
        glfwPollEvents();

        m_WindowShouldClose = static_cast<bool>(glfwWindowShouldClose(m_Window));
    }

    void DesktopDisplay::GLFWKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        // only send on pressed and on releaseed event
        if (action != GLFW_PRESS && action != GLFW_RELEASE)
            return;

        InputEventKeyboard keyEvent{};
        keyEvent.Code = static_cast<Keycode>(key);
        keyEvent.Pressed = action == GLFW_PRESS;

        InputEvent event{keyEvent};
        ASEngine::GetInstance().QueueInputEvent(event);
    }

    void DesktopDisplay::GLFWCursorPosCallback(GLFWwindow *window, double xpos, double ypos)
    {
        InputEventMouseMove mouseMoveEvent{};
        mouseMoveEvent.Position = Vector2{static_cast<float>(xpos), static_cast<float>(ypos)};

        InputEvent event{mouseMoveEvent};
        ASEngine::GetInstance().QueueInputEvent(event);
    }

    void DesktopDisplay::GLFWMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
    {
        // only send on pressed and on releaseed event
        if (action != GLFW_PRESS && action != GLFW_RELEASE)
            return;


        InputEventMouseButton mouseButtonEvent{};
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            mouseButtonEvent.Button = MouseButton::LEFT;
            break;

        case GLFW_MOUSE_BUTTON_RIGHT:
            mouseButtonEvent.Button = MouseButton::RIGHT;
            break;

        case GLFW_MOUSE_BUTTON_MIDDLE:
            mouseButtonEvent.Button = MouseButton::MIDDLE;
            break;
        default:
            mouseButtonEvent.Button = MouseButton::NONE;
            break;
        }

        // don't push unsupported buttons
        if (mouseButtonEvent.Button == MouseButton::NONE)
            return;

        // get mouse position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        mouseButtonEvent.Position = Vector2{static_cast<float>(xpos), static_cast<float>(ypos)};

        // pressed state
        mouseButtonEvent.Pressed = action == GLFW_PRESS;

        // push event
        InputEvent event{mouseButtonEvent};
        ASEngine::GetInstance().QueueInputEvent(event);
    }

} // namespace ASEngine
