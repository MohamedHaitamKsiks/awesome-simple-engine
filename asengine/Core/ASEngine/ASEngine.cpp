#include "ASEngine.h"

#include "Core/FileSystem/File.h"
#include "Core/String/UniqueStringManager.h"
#include "Core/Registry/Registry.h"
#include "Core/Debug/Debug.h"

#include "Core/Serialization/Json.h"

#include "ECS/EntityManager.h"
#include "ECS/ArchetypeManager.h"
#include "ECS/ComponentManager.h"

#include "Scene/Scene.h"
#include "Scene/SceneManager.h"

//#include "Audio/AudioEngine.h"
//#include "Renderer/Viewport.h"

namespace ASEngine
{

    void ASEngine::Init()
    {
        ModuleManager::GetInstance().Registry();
        SystemManager::GetInstance().Init();
    }

    void ASEngine::Setup()
    {
        // load project settings
        LoadProjectSettings();

        // register application systems and modules
        RegisterBuiltInSystems();
        Debug::Log("ASEngine setup complete");
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
        ASENGINE_REGISTER_SYSTEM(ArchetypeManager);
        ASENGINE_REGISTER_SYSTEM(EntityManager);
        
        ASENGINE_REGISTER_RESOURCE_CLASS(Scene);
        ASENGINE_REGISTER_SYSTEM(SceneManager);
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
        float fixedTimeStep = m_Settings.Time.FixedTimeStep;

        while (m_FixedTimer >= fixedTimeStep)
        {
            systemManager.FixedUpdate(fixedTimeStep * m_TimeScale);
            m_FixedTimer -= fixedTimeStep;
        }

        // call normal update
        systemManager.Update(delta * m_TimeScale);

        // destroy all enities in queue
        EntityManager::GetInstance().CleanDestroyQueue();
    }


    void ASEngine::LoadProjectSettings()
    {
        // load settigs file
        File settingsFile;
        settingsFile.Open("project.settings.json", FileOpenMode::READ);
        
        // read settings as json
        std::string settingsString = settingsFile.ReadText();
        Json settingsObject = Json::parse(settingsString);

        // deserialize settings
        Serializer::Deserialize(settingsObject, m_Settings);
    }


} // ASEngine

