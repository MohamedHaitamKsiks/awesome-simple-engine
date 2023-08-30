#include "Window.h"

namespace ASEngine
{

    void Window::ISetSize(int width, int height)
    {
        m_Width = width;
        m_Height = height;

        m_Size = vec2{(float)width, (float)height};

        m_ResizeSignal.Emit(width, height);
    }

    void Window::ISetFullscreen(bool fullscreen)
    {
        if (m_Fullscreen == fullscreen)
            return;

        m_Fullscreen = fullscreen;
        m_SetFullscreenSignal.Emit(fullscreen);
    }


    void Window::ISetTitle(const std::string& title)
    {
        m_Title = title;
        m_SetTitleSignal.Emit(title);
    }

} // namespace ASEngine
