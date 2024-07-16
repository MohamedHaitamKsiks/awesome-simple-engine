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

        // set keyboard callback
        emscripten_set_keydown_callback(_ASENGINE_WEB_CANVAS_ID, nullptr, true, WebDisplay::EMKeyDownCallback);
        emscripten_set_keyup_callback(_ASENGINE_WEB_CANVAS_ID, nullptr, true, WebDisplay::EMKeyUpCallback);

        // set mouse callbacks
        emscripten_set_mousemove_callback(_ASENGINE_WEB_CANVAS_ID, nullptr, true, WebDisplay::EMMoveMouseCallback);
        emscripten_set_mousedown_callback(_ASENGINE_WEB_CANVAS_ID, nullptr, true, WebDisplay::EMMouseButtonDownCallback);
        emscripten_set_mouseup_callback(_ASENGINE_WEB_CANVAS_ID, nullptr, true, WebDisplay::EMMouseButtonUpCallback);
    }

    void WebDisplay::TerminateImp()
    {
        // delete webgl context
        emscripten_webgl_destroy_context(m_WebGLContext);
    }

    void WebDisplay::SetWindowSizeImp(int width, int height)
    {
        emscripten_set_canvas_element_size(_ASENGINE_WEB_CANVAS_ID, width, height);
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

    EM_BOOL WebDisplay::EMKeyDownCallback(int eventType, const EmscriptenKeyboardEvent *emKeyEvent, void *userData)
    {
        return EMKeyCallback(eventType, emKeyEvent, userData, true);
    }

    EM_BOOL WebDisplay::EMKeyUpCallback(int eventType, const EmscriptenKeyboardEvent *emKeyEvent, void *userData)
    {
        return EMKeyCallback(eventType, emKeyEvent, userData, false);
    }

    EM_BOOL WebDisplay::EMKeyCallback(int eventType, const EmscriptenKeyboardEvent *emKeyEvent, void *userData, bool keydown)
    {
        InputEventKeyboard keyEvent{};
        keyEvent.Code = static_cast<Keycode>(emKeyEvent->keyCode);
        keyEvent.Pressed = keydown;

        InputEvent event{keyEvent};
        ASEngine::GetInstance().QueueInputEvent(event);
        return EM_FALSE;
    }

    EM_BOOL WebDisplay::EMMoveMouseCallback(int eventType, const EmscriptenMouseEvent *emMouseEvent, void *userData)
    {
        InputEventMouseMove mouseMoveEvent{};
        mouseMoveEvent.Position = Vector2{static_cast<float>(emMouseEvent->targetX), static_cast<float>(emMouseEvent->targetY)};

        InputEvent event{mouseMoveEvent};
        ASEngine::GetInstance().QueueInputEvent(event);
        return EM_FALSE;
    }

    EM_BOOL WebDisplay::EMMouseButtonCallback(int eventType, const EmscriptenMouseEvent *emMouseEvent, void *userData, bool mousedown)
    {
        InputEventMouseButton mouseButtonEvent{};
        switch (emMouseEvent->button)
        {
        case 0:
            mouseButtonEvent.Button = MouseButton::LEFT;
            break;
        case 2:
            mouseButtonEvent.Button = MouseButton::RIGHT;
            break;
        case 1:
            mouseButtonEvent.Button = MouseButton::MIDDLE;
            break;
        default:
            mouseButtonEvent.Button = MouseButton::NONE;
            break;
        }

        // don't push unsupported buttons
        if (mouseButtonEvent.Button == MouseButton::NONE)
            return EM_FALSE;

        // get mouse position
        mouseButtonEvent.Position = Vector2{static_cast<float>(emMouseEvent->targetX), static_cast<float>(emMouseEvent->targetY)};

        // pressed state
        mouseButtonEvent.Pressed = mousedown;

        // push event
        InputEvent event{mouseButtonEvent};
        ASEngine::GetInstance().QueueInputEvent(event);

        return EM_FALSE;
    }

    EM_BOOL WebDisplay::EMMouseButtonDownCallback(int eventType, const EmscriptenMouseEvent *emMouseEvent, void *userData)
    {
        return EMMouseButtonCallback(eventType, emMouseEvent, userData, true);
    }

    EM_BOOL WebDisplay::EMMouseButtonUpCallback(int eventType, const EmscriptenMouseEvent *emMouseEvent, void *userData)
    {
        return EMMouseButtonCallback(eventType, emMouseEvent, userData, false);
    }

} // namespace ASEngine
