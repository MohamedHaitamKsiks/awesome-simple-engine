#include "DesktopDisplay.h"
#include "Core/ASEngine/ASEngine.h"

namespace ASEngine
{
    void DesktopDisplay::Init()
    {
        if (!glfwInit())
        {
            glfwTerminate();
            return;
        }

        // get settings
        const auto& displaySettings = ASEngine::GetInstance().GetSettings().Display;
        const auto& windowSettings = displaySettings.Window;
        const auto& viewportSettings = displaySettings.Viewport;
        const auto& renderingSettings = displaySettings.Rendering;

        // create window with default values
        m_Window = glfwCreateWindow(640 * 2, 480 * 2, "ASEngine Desktop Window", NULL, NULL);
        
        // set
        glfwMakeContextCurrent(m_Window);
    }

    void DesktopDisplay::Terminate()
    {
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

    void DesktopDisplay::SetViewportSizeImp(uint32_t width, uint32_t height)
    {
    }

    void DesktopDisplay::SetFullscreenImp(bool fullscreen)
    {
        if (fullscreen)
        {
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
        else
        {
            // set windowed
            glfwSetWindowMonitor(m_Window, NULL, m_PositionX, m_PositionY, m_WindowedWindowWidth, m_WindowedWindowHeight, 0);
            SetWindowSize(m_WindowedWindowWidth, m_WindowedWindowHeight);
        }
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

} // namespace ASEngine
