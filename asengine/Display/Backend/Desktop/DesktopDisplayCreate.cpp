#include "DesktopDisplay.h"
#include "Display/Display.h"
#include "ECS/SystemManager.h"
#include "Renderer/Backend/RendererBackend.h"

namespace ASEngine
{
    void Display::Create(Renderer::Backend backend)
    {
        // register display 
        ASENGINE_REGISTER_SYSTEM(DesktopDisplay);

        // create opengl renderer
        RendererBackend::CreateOpenGLRenderer();
    }
} // namespace ASEngine
