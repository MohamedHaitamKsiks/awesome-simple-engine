#include "Display.h"
#include "Core/ASEngine/ASEngine.h"


namespace ASEngine
{
    void Display::Init()
    {
        InitImp();
    }

    void Display::Terminate()
    {
        TerminateImp();
    }

    void Display::SetWindowSize(uint32_t width, uint32_t height)
    {
        m_WindowWidth = width;
        m_WindowHeight = height;

        SetWindowSizeImp(width, height);
        m_EmittingWindowSignal = true;
    }

    void Display::SetFullscreen(bool fullscreen)
    {
        if (fullscreen == m_Fullscreen)
            return;
        
        m_Fullscreen = fullscreen;
        SetFullscreenImp(fullscreen);
    }

    void Display::SetKeepAspectRatio(bool keep)
    {
        m_KeepAspectRatio = keep;
    }

    void Display::SetWindowTitle(const std::string &title)
    {
        m_WindowTitle = title;
        SetWindowTitleImp(title);
    }

    void Display::BeginFrame()
    {
        BeginFrameImp();

        // resize if necessary
        if (m_EmittingWindowSignal)
        {
            m_WindowResizeSignal.Emit(m_WindowWidth, m_WindowHeight);
            m_EmittingWindowSignal = false;
        }
    }

    void Display::EndFrame()
    {
        EndFrameImp();
    }

} // namespace ASEngine
