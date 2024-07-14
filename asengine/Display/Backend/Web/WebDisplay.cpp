#include "WebDisplay.h"
#include "Core/ASEngine/ASEngine.h"


#define _ASENGINE_WEB_CANVAS_ID "#canvas"

namespace ASEngine
{
    void WebDisplay::InitImp()
    {
        // get settings
        const auto& displaySettings = ASEngine::GetInstance().GetSettings().Display;
        const auto& windowSettings = displaySettings.Window;
        const auto& applicationSettings = ASEngine::GetInstance().GetSettings().Application;

        // create webgl attributes
        EmscriptenWebGLContextAttributes webGLAttributes{};
        webGLAttributes.majorVersion = 2;
        webGLAttributes.minorVersion = 0;

        // create webgl context
        m_WebGLContext = emscripten_webgl_create_context(_ASENGINE_WEB_CANVAS_ID, &webGLAttributes);
        emscripten_webgl_make_context_current(m_WebGLContext);

        // set settings
        SetWindowSize(windowSettings.Width, windowSettings.Height);
        SetWindowTitle(applicationSettings.Name);
        SetFullscreen(windowSettings.Fullscreen);
        SetKeepAspectRatio(windowSettings.KeepAspectRatio);
    }

    void WebDisplay::TerminateImp()
    {
        // delete webgl context
        emscripten_webgl_destroy_context(m_WebGLContext);
    }

    void WebDisplay::SetWindowSizeImp(int width, int height)
    {
        emscripten_set_canvas_size(width, height);
    }

    void WebDisplay::SetWindowTitleImp(const std::string &title)
    {
        emscripten_set_window_title(title.c_str());
    }

    void WebDisplay::SetFullscreenImp(bool fullscreen)
    {
        // exit full screen
        if (!fullscreen)
        {
            emscripten_exit_fullscreen();
            SetWindowSize(m_WindowedWindowWidth, m_WindowedWindowHeight);
            return;
        }

        // set fullscreen 

        // get current display size 
        m_WindowedWindowWidth = GetWindowWidth();
        m_WindowedWindowHeight = GetWindowHeight();

        // set to fullscreen
        emscripten_request_fullscreen(_ASENGINE_WEB_CANVAS_ID, 1);

        // get screen size
        int width, height;
        emscripten_get_screen_size(&width, &height);

        // resize display
        SetWindowSize(static_cast<uint32_t>(width), static_cast<uint32_t>(height));
    }

    void WebDisplay::BeginFrameImp()
    {
    }

    void WebDisplay::EndFrameImp()
    {
        emscripten_webgl_commit_frame();
    }

} // namespace ASEngine
