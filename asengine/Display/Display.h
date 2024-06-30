#ifndef __ASENGINE_DISPLAY_H
#define __ASENGINE_DISPLAY_H

#include "Core/Singleton/Singleton.h"
#include "Core/Signal/Signal.h"

#include "Renderer/Renderer.h"

#include "ECS/System.h"

#include "API/API.h"

namespace ASEngine
{
    // game's display: singleton = only one window
    class ASENGINE_API Display : public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(Display);
    public:
        virtual ~Display() {}; // make it polymorphic

        // create display
        static void Create(Renderer::Backend backend);

        // set window size (makes your go out of fullscreen)
        void SetWindowSize(uint32_t width, uint32_t height);

        // get window width
        inline uint32_t GetWindowWidth() const
        {
            return m_WindowHeight;
        }

        // get window height
        inline uint32_t GetWindowHeight() const
        {
            return m_WindowHeight;
        }

        // set viewport size
        void SetViewportSize(uint32_t width, uint32_t height);

        // get viewport width
        inline uint32_t GetViewportWidth() const
        {
            return m_ViewportWidth;
        }

        // get viewport height
        inline uint32_t GetViewportHeight() const
        {
            return m_ViewportHeight;
        }

        // set fullscreen 
        void SetFullscreen(bool fullscreen);

        // get current fullscreen state
        inline bool IsFullscreen() const
        {
            return m_Fullscreen;
        }

        // set aspect ratio mode
        void SetKeepAspectRatio(bool keep);

        // get current fullscreen state
        inline bool IsKeepAspectRatio() const
        {
            return m_KeepAspectRatio;
        }

        // get aspect ratio
        inline float GetAspectRatio() const
        {
            return m_AspectRatio;
        }

        // set window title
        void SetWindowTitle(const std::string& title);

        // get window title
        inline const std::string& GetWindowTitle() const
        {
            return m_WindowTitle;
        }

        // begin frame
        void BeginFrame();

        // end frame
        void EndFrame();

        // is closed
        bool IsWindowShouldClose() const
        {
            return m_WindowShouldClose;
        }

        // get window signal
        inline Signal<uint32_t, uint32_t>& GetWindowResizeSignal()
        {
            return m_WindowResizeSignal;
        }

    protected:
        bool m_WindowShouldClose = false;

        virtual void InitImp() = 0;
        virtual void TerminateImp() = 0;
        virtual void SetWindowSizeImp(int width, int height) = 0;
        virtual void SetWindowTitleImp(const std::string& title) = 0;
        virtual void SetViewportSizeImp(uint32_t width, uint32_t height) = 0;
        virtual void SetFullscreenImp(bool fullscreen) = 0;
        virtual void BeginFrameImp() = 0;
        virtual void EndFrameImp() = 0;

    private:
        // window size
        uint32_t m_WindowWidth = 0;
        uint32_t m_WindowHeight = 0;

        // viewport size
        uint32_t m_ViewportWidth = 0;
        uint32_t m_ViewportHeight = 0;

        // fullscreen
        bool m_Fullscreen = false;
        
        // aspect ration
        float m_AspectRatio = 1.77f; // 16:9
        bool m_KeepAspectRatio = true;

        // title
        std::string m_WindowTitle = "";

        // window resize signal
        bool m_EmittingWindowSignal = false;
        Signal<uint32_t, uint32_t> m_WindowResizeSignal{};

        void Init() override;
        void Terminate() override;
    };
} // namespace ASEngine



#endif // __ASENGINE_DISPLAY_H