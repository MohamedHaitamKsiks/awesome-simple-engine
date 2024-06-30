#include "SceneManager.h"
#include "ECS/EntityManager.h"
#include "Core/ASEngine/ASEngine.h"

namespace ASEngine
{
    void SceneManager::ChangeSceneTo(ResourceRef<Scene> scene)
    {
        EntityManager::GetInstance().DestroyAll();
        scene->Instanciate();

        m_CurrentScene = scene;
    }

    void SceneManager::ReloadCurrentScene()
    {
        ChangeSceneTo(m_CurrentScene);
    }

    void SceneManager::Init()
    {
        const auto& settings = ASEngine::GetInstance().GetSettings();
        UniqueString mainScenePath = UniqueString(settings.Application.MainScene);

        ResourceRef<Scene> mainScene = Scene::GetResourceClass().Load(mainScenePath);
        ChangeSceneTo(mainScene);
    }

} // namespace ASEngine
