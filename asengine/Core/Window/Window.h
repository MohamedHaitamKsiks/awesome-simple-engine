#ifndef ASENGINE_WINDOW_H
#define ASENGINE_WINDOW_H

#include "Core/Math/Vector2.h"
#include "Core/Signal/Signal.h"
#include "Core/Singleton/Singleton.h"

#include "ECS/System.h"

namespace ASEngine
{
    // game's window: singleton
    class Window: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(Window);
    public:
        // set window size to
        void SetSize(int width, int height);

        //get window size
        inline const Vector2& GetSize() const
        {
            return m_Size;
        }

        // set fullscreen 
        void SetFullscreen(bool fullscreen);

        // get current fullscreen state
        bool IsFullscreen() const
        {
            return m_Fullscreen;
        }

        // set aspect ratio mode
        void SetKeepAspectRatio(bool keep);

        // get current fullscreen state
        inline bool IsKeepAspectRatio() const
        {
            return m_AspectRatio;
        }

        // set window title
        void SetTitle(const std::string& title);

        // get window title
        inline const std::string& GetTitle() const
        {
            return m_Title;
        }
        
        inline Signal<int, int>& GetResizeSignal()
        {
            return m_ResizeSignal;
        }

        inline Signal<bool> &GetFullscreenSignal()
        {
            return m_SetFullscreenSignal;
        }

        inline Signal<std::string> &GetTitleSignal()
        {
            return m_SetTitleSignal;
        }

    private:
        // signals
        Signal<int, int> m_ResizeSignal{};
        Signal<bool> m_SetFullscreenSignal{};
        Signal<std::string> m_SetTitleSignal{};

        int m_Width = -1;
        int m_Height = -1;
        Vector2 m_Size = Vector2::ZERO();

        bool m_Fullscreen = false;
        float m_AspectRatio = 1.77f; // 16:9
        bool m_KeepAspectRatio = true;
        std::string m_Title;
    };
} // namespace ASEngine



#endif // ASENGINE_WINDOW_H