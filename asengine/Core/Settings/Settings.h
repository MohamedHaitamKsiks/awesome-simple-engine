#ifndef __ASENGINE_SETTINGS_H
#define __ASENGINE_SETTINGS_H

#include <string>
#include "Renderer/Renderer.h"
#include "API/API.h"

namespace ASEngine
{
    // time settings
    struct ASENGINE_API TimeSettings
    {
        float FixedTimeStep = 0.02f;
    };

    // application settings
    struct ASENGINE_API ApplicationSettings
    {
        std::string Name = "ASEngine-Project";
        std::string MainScene = "";
    };

    // viewport settings
    struct ASENGINE_API ViewportSettings
    {
        uint32_t Width = 0;
        uint32_t Height = 0;
    };

    // window settings
    struct ASENGINE_API WindowSettings
    {
        uint32_t Width = 0;
        uint32_t Height = 0;
        bool KeepAspectRatio = false;
        bool Fullscreen = false;
    };

    // renderer settings
    struct ASENGINE_API RenderingSettings
    {
        Renderer::Backend Backend = Renderer::Backend::NONE;
    };

    // display settings
    struct ASENGINE_API DisplaySettings
    {
        ViewportSettings Viewport;
        WindowSettings Window;
        RenderingSettings Rendering;
    };

    // asengine settings
    struct ASENGINE_API Settings
    {
        ApplicationSettings Application;
        DisplaySettings Display;
        TimeSettings Time;
    };
} // namespace ASEngine


#endif // __ASENGINE_SETTINGS_H