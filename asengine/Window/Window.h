#ifndef __ASENGINE_WINDOW_H
#define __ASENGINE_WINDOW_H

#include "Core/Math/Vector2.h"
#include "Core/Signal/Signal.h"
#include "Core/Singleton/Singleton.h"

#include "ECS/System.h"

namespace ASEngine
{
    // game's window: singleton = only one window 
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
    private:
        int m_Width = -1;
        int m_Height = -1;
        Vector2 m_Size = Vector2::ZERO();

        bool m_Fullscreen = false;
        float m_AspectRatio = 1.77f; // 16:9
        bool m_KeepAspectRatio = true;
        std::string m_Title;
    };
} // namespace ASEngine



#endif // __ASENGINE_WINDOW_H