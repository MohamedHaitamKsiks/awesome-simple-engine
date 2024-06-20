#ifndef __ASENGINE_DESKTOP_DISPLAY_H
#define __ASENGINE_DESKTOP_DISPLAY_H

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Display/Display.h"

namespace ASEngine
{
    // desktop display using glfw
    class DesktopDisplay: public Display
    {
    public:
        ~DesktopDisplay() {}
    
    private:
        GLFWwindow *m_Window = nullptr;

        uint32_t m_WindowedWindowWidth = 0;
        uint32_t m_WindowedWindowHeight = 0;

        uint32_t m_PositionX = 0;
        uint32_t m_PositionY = 0;

        // implementation for desktop
        void SetWindowSizeImp(int width, int height) override;
        void SetWindowTitleImp(const std::string &title) override;
        void SetViewportSizeImp(uint32_t width, uint32_t height) override;
        void SetFullscreenImp(bool fullscreen) override;
        void BeginFrameImp() override;
        void EndFrameImp() override;

        void Init() override;
        void Terminate() override;
    };
} // namespace ASEngine

#endif // __ASENGINE_DESKTOP_DISPLAY_H