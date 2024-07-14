#include "WebDisplay.h"
#include "Display/Display.h"
#include "ECS/SystemManager.h"
#include "Renderer/Backend/RendererBackend.h"

#include "Core/ASEngine/ASEngine.h"
#include "Core/Settings/Settings.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Debug/Debug.h"

namespace ASEngine
{
    void Display::Create()
    {
        // register display 
        ASENGINE_REGISTER_SYSTEM(WebDisplay);

        const auto &renderingSettings = ASEngine::GetInstance().GetSettings().Display.Rendering;
        // don't allow vulkan
        if (renderingSettings.Backend != Renderer::Backend::OPENGL)
        {
            std::string backendName = Serializer::Serialize(renderingSettings.Backend).get<std::string>();
            Debug::Error(backendName, ": Unsupported Backend!");
            Debug::Error("Web only supports OpenGL for rendering.");
        }

        // create opengl renderer
        Debug::Log("Using OpenGL Renderer.");
        RendererBackend::CreateOpenGLRenderer();
    }
} // namespace ASEngine
