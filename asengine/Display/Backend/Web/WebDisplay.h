#ifndef __ASENGINE_WEB_DISPLAY_H
#define __ASENGINE_WEB_DISPLAY_H

#include "Display/Display.h"

#include <emscripten.h>
#include <emscripten/html5.h>

namespace ASEngine
{
    // web display using glfw
    class WebDisplay: public Display
    {
    public:
        ~WebDisplay() {}
    
    private:
        uint32_t m_WindowedWindowWidth = 0;
        uint32_t m_WindowedWindowHeight = 0;

        EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_WebGLContext = 0;

        // implementation for desktop
        void InitImp() override;
        void TerminateImp() override;
        void SetWindowSizeImp(int width, int height) override;
        void SetWindowTitleImp(const std::string &title) override;
        void SetFullscreenImp(bool fullscreen) override;
        void BeginFrameImp() override;
        void EndFrameImp() override;
    };
} // namespace ASEngine

#endif // __ASENGINE_DESKTOP_WEB_H