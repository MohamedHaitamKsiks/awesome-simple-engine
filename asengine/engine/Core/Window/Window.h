#ifndef ASENGINE_WINDOW_H
#define ASENGINE_WINDOW_H

#include "Core/Math/vec2.h"
#include "Core/Signals/Signal.h"
#include "Core/Singleton/Singleton.h"

namespace ASEngine
{
    // game's window: singleton
    class Window: public Singleton<Window>
    {
    public:
        // set window size to
        static inline void SetSize(int width, int height) { GetSingleton()->ISetSize(width, height); };
        //get window size
        static inline vec2 GetSize() { return GetSingleton()->m_Size; };

        // set fullscreen 
        static inline void SetFullscreen(bool fullscreen) { GetSingleton()->ISetFullscreen(fullscreen); };
        // get current fullscreen state
        static inline bool IsFullscreen() { return GetSingleton()->m_Fullscreen; };

        // set aspect ratio mode
        static inline void SetKeepAspectRatio(bool keep) { GetSingleton()->m_KeepAspectRatio = keep; };
        // get current fullscreen state
        static inline bool IsKeepAspectRatio() { return GetSingleton()->m_KeepAspectRatio; };

        // set window title
        static inline void SetTitle(const std::string& title) { GetSingleton()->ISetTitle(title); };
        // get window title
        static inline std::string GetTitle() { return GetSingleton()->m_Title; };

        
        static inline Signal<int, int>& ResizeSignal() { return GetSingleton()->m_ResizeSignal; };
        static inline Signal<bool> &FullscreenSignal() { return GetSingleton()->m_SetFullscreenSignal; };
        static inline Signal<std::string> &TitleSignal() { return GetSingleton()->m_SetTitleSignal; };

    private:
        // signals
        Signal<int, int> m_ResizeSignal{};
        Signal<bool> m_SetFullscreenSignal{};
        Signal<std::string> m_SetTitleSignal{};

        int m_Width = -1;
        int m_Height = -1;
        vec2 m_Size = vec2::ZERO();

        bool m_Fullscreen = false;
        float m_AspectRatio = 1.77f; // 16:9
        bool m_KeepAspectRatio = true;
        std::string m_Title;

        // internal functions
        void ISetSize(int width, int height);
        void ISetFullscreen(bool fullscreen);
        void ISetTitle(const std::string &title);
    };
} // namespace ASEngine



#endif // ASENGINE_WINDOW_H