#ifndef __ASENGINE_SETTINGS_H
#define __ASENGINE_SETTINGS_H

#include <string>
#include "Renderer/Renderer.h"

namespace ASEngine
{
    // time settings
    struct TimeSettings
    {
        float FixedTimeStep = 0.02f;
    };

    // application settings
    struct ApplicationSettings
    {
        std::string Name = "ASEngine-Project";
    };

    // viewport settings
    struct ViewportSettings
    {
        uint32_t Width = 0;
        uint32_t Height = 0;
    };

    // window settings
    struct WindowSettings
    {
        uint32_t Width = 0;
        uint32_t Height = 0;
        bool KeepAspectRatio = false;
        bool Fullscreen = false;
    };

    // renderer settings
    struct RenderingSettings
    {
        Renderer::Backend Backend = Renderer::Backend::NONE;
    };

    // display settings
    struct DisplaySettings
    {
        ViewportSettings Viewport;
        WindowSettings Window;
        RenderingSettings Rendering;
    };

    // asengine settings
    struct Settings
    {
        ApplicationSettings Application;
        DisplaySettings Display;
        TimeSettings Time;
    };
} // namespace ASEngine


#endif // __ASENGINE_SETTINGS_H