#include "Settings.h"
#include "Core/Serialization/SerializeStruct.h"


namespace ASEngine
{
    ASENGINE_SERIALIZE_STRUCT(TimeSettings, 
        FixedTimeStep
    );  

    ASENGINE_SERIALIZE_STRUCT(ApplicationSettings,
        Name
    );

    ASENGINE_SERIALIZE_STRUCT(ViewportSettings,
        Width,
        Height
    );

    ASENGINE_SERIALIZE_STRUCT(WindowSettings,
        Width,
        Height,
        KeepAspectRatio,
        Fullscreen
    );

    ASENGINE_SERIALIZE_STRUCT(RenderingSettings,
        Backend
    );

    ASENGINE_SERIALIZE_STRUCT(DisplaySettings,
        Viewport,
        Window,
        Rendering
    );

    ASENGINE_SERIALIZE_STRUCT(Settings,
        Application,
        Display,
        Time
    );
} // namespace ASEngine
