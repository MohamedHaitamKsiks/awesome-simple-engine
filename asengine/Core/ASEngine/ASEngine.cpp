#include "ASEngine.h"

#include "Core/FileSystem/File.h"
#include "Core/String/UniqueStringManager.h"
#include "Core/Registry/Registry.h"
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

    void ASEngine::Init()
    {
        ModuleManager::GetInstance().Registry();

        // load project settings
        LoadProjectSettings();

        SystemManager::GetInstance().Init();
        Debug::Log("ASEngine init complete");
    }

    void ASEngine::Setup()
    {
        // register application systems and modules
        RegisterBuiltInSystems();
    }

    void ASEngine::Setup(int argc, char *argv[])
    {
        // add arguments to application
        for (int i = 0; i < argc; i++)
        {
            std::string arg = std::string(argv[i]);
            m_Arguments.push_back(arg);
        }
        Setup();
    }

    void ASEngine::RegisterBuiltInSystems()
    {
        SystemManager& systemManager = SystemManager::GetInstance();

        systemManager.RegisterSystem<ComponentManager>();
        systemManager.RegisterSystem<ArchetypeManager>();
        systemManager.RegisterSystem<EntityManager>();
    }

    void ASEngine::Terminate()
    {
        SystemManager::GetInstance().Terminate();
    }

    void ASEngine::Update(float delta)
    {
        // get system manager
        SystemManager& systemManager = SystemManager::GetInstance();

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

        // call render
        systemManager.Render();

        // destroy all enities in queue
        EntityManager::GetInstance().CleanDestroyQueue();
    }


    void ASEngine::LoadProjectSettings()
    {
        /*//load json file
        File projectSettingsFile;
        projectSettingsFile.Open("project.settings.json", FileOpenMode::READ);
        std::string projectSettingsString = projectSettingsFile.ReadText();
        projectSettingsFile.Close();

        //parse to json
        Json projectSettings = Json::parse(projectSettingsString);

        // set project name
        std::string projectName = projectSettings["name"].get<std::string>();
        //Window::GetInstance().SetTitle(projectName);

        // set view port
        int viewportWidth = projectSettings["viewport"]["size"]["width"].get<int>();
        int viewportHeight = projectSettings["viewport"]["size"]["height"].get<int>();
        // Viewport::GetInstance().SetSize(viewportWidth, viewportHeight);

        // set window size
        int windowWidth = projectSettings["window"]["size"]["width"].get<int>();
        int windowHeight = projectSettings["window"]["size"]["height"].get<int>();
        // Window::GetInstance().SetSize(windowWidth, windowHeight);

        // set fullscreen mode
        bool windowIsFullscreen = projectSettings["window"]["fullscreen"].get<bool>();
        // Window::GetInstance().SetFullscreen(windowIsFullscreen);

        // set fixed time 
        Time::FixedTimeStep = projectSettings["fixedTimeStep"].get<float>();
        Time::TimeScale = 1.0f;*/
    }


} // ASEngine

