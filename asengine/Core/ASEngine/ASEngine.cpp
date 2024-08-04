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

#include <chrono>
#define SEC_TO_MICRO 1000000.0f

namespace ASEngine
{

    void ASEngine::Init()
    {
        ModuleManager::GetInstance().Registry();

        // register the world and scene manager
        ASENGINE_REGISTER_SYSTEM(EntityManager);
        ASENGINE_REGISTER_SYSTEM(SceneManager);

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

    void ASEngine::DestroyGlobalAttribute(const std::string &name)
    {
        if (m_GlobalAttributes.find(name) == m_GlobalAttributes.end())
            return;

        GlobalAttribute& attribute = m_GlobalAttributes[name];
        attribute.Destroy();
    }

    void ASEngine::RegisterBuiltInSystems()
    {
        ASENGINE_REGISTER_SYSTEM(ArchetypeManager);
        ASENGINE_REGISTER_RESOURCE_CLASS(Scene);
    }

    void ASEngine::Terminate()
    {
        SystemManager::GetInstance().Terminate();

        // remove global attributes
        for (auto& [name, attribute]: m_GlobalAttributes)
        {
            attribute.Destroy();
        }

        m_GlobalAttributes.clear();
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

    int ASEngine::Run(std::function<void(float)> updateFunction)
    {
        float delta = 0.02f;

        while(!m_IsExit)
        {
            // get time now
            const auto pastTime = std::chrono::high_resolution_clock::now();

            updateFunction(delta);

            // compute delta
            const auto currentTime = std::chrono::high_resolution_clock::now();
            delta = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - pastTime).count() / SEC_TO_MICRO;

        };

        return m_ExitReturnCode;
    }

    void ASEngine::Exit(int code)
    {
        if (m_IsExit)
            return;

        m_IsExit = true;
        m_ExitReturnCode = code;
    }

    void ASEngine::LoadProjectSettings()
    {
        // load settigs file
        File settingsFile;
        settingsFile.Open("assets://project.settings.json", FileOpenMode::READ);

        // read settings as json
        std::string settingsString = settingsFile.ReadText();
        Json settingsObject = Json::parse(settingsString);

        // deserialize settings
        Serializer::Deserialize(settingsObject, m_Settings);
    }


} // ASEngine
