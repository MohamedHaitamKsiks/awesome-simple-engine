#include "Window.h"

namespace ASEngine
{

    void Window::SetSize(int width, int height)
    {
        m_Width = width;
        m_Height = height;

        m_Size = Vector2{(float)width, (float)height};

        m_ResizeSignal.Emit(width, height);
    }

    void Window::SetFullscreen(bool fullscreen)
    {
        if (m_Fullscreen == fullscreen)
            return;

        m_Fullscreen = fullscreen;
        m_SetFullscreenSignal.Emit(fullscreen);
    }

    void Window::SetKeepAspectRatio(bool keep)
    {
        m_KeepAspectRatio = keep;
        m_ResizeSignal.Emit(m_Width, m_Height);
    }

    void Window::SetTitle(const std::string& title)
    {
        m_Title = title;
        m_SetTitleSignal.Emit(title);
    }

} // namespace ASEngine
