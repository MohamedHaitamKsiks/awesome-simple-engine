#include "Application.h"

#include "Core/FileSystem/File.h"
#include "Core/String/UniqueStringManager.h"
#include "Core/Registry/Registry.h"
#include "Core/Window/Window.h"
#include "Core/Time/Time.h"
#include "Core/Debug/Debug.h"

#include "Core/Serialization/Json.h"

#include "ECS/EntityManager.h"
#include "ECS/ArchetypeManager.h"
#include "ECS/ComponentManager.h"

//#include "Audio/AudioEngine.h"
//#include "Renderer/Viewport.h"

namespace ASEngine
{

    void Application::Init()
    {
        Registry();
        ModuleManager::GetInstance().Registry();

        // load project settings
        LoadProjectSettings();

        SystemManager::GetInstance().Init();
        Debug::Log("Application init complete");
    }

    void Application::Setup()
    {
        // register application systems and modules
        RegisterBuiltInSystems();
    }

    void Application::RegisterBuiltInSystems()
    {
        SystemManager& systemManager = SystemManager::GetInstance();
        systemManager.RegisterSystem<Window>();
        systemManager.RegisterSystem<ComponentManager>();
        systemManager.RegisterSystem<ArchetypeManager>();
        systemManager.RegisterSystem<EntityManager>();
    }

    void Application::Terminate()
    {
        SystemManager::GetInstance().Terminate();
    }

    void Application::Update(float delta)
    {
        // get system manager
        auto& systemManager = SystemManager::GetInstance();

        // process input
        for (auto& event: m_InputEventQueue)
        {
            systemManager.OnInputEvent(event);
        }
        m_InputEventQueue.clear();

        // call fixed steps
        m_FixedTimer += delta;
        while (m_FixedTimer >= Time::FixedTimeStep)
        {
            systemManager.FixedUpdate(Time::FixedTimeStep * Time::TimeScale);
            m_FixedTimer -= Time::FixedTimeStep;
        }

        // call normal update
        systemManager.Update(delta * Time::TimeScale);

        // destroy all enities in queue
        EntityManager::GetInstance().CleanDestroyQueue();
    }


    void Application::LoadProjectSettings()
    {
        //load json file
        File projectSettingsFile;
        projectSettingsFile.Open("project.settings.json", FileOpenMode::READ);
        std::string projectSettingsString = projectSettingsFile.ReadText();
        projectSettingsFile.Close();

        //parse to json
        Json projectSettings = Json::parse(projectSettingsString);

        // set project name
        std::string projectName = projectSettings["name"].get<std::string>();
        Window::GetInstance().SetTitle(projectName);

        // set view port
        int viewportWidth = projectSettings["viewport"]["size"]["width"].get<int>();
        int viewportHeight = projectSettings["viewport"]["size"]["height"].get<int>();
        // Viewport::GetInstance().SetSize(viewportWidth, viewportHeight);

        // set window size
        int windowWidth = projectSettings["window"]["size"]["width"].get<int>();
        int windowHeight = projectSettings["window"]["size"]["height"].get<int>();
        Window::GetInstance().SetSize(windowWidth, windowHeight);

        // set fullscreen mode
        bool windowIsFullscreen = projectSettings["window"]["fullscreen"].get<bool>();
        Window::GetInstance().SetFullscreen(windowIsFullscreen);

        // set fixed time 
        Time::FixedTimeStep = projectSettings["fixedTimeStep"].get<float>();
        Time::TimeScale = 1.0f;
    }


} // ASEngine

