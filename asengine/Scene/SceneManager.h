#ifndef __ASENGINE_SCENE_MANAGER_H
#define __ASENGINE_SCENE_MANAGER_H

#include "Core/Singleton/Singleton.h"
#include "ECS/System.h"

#include "Scene.h"


namespace ASEngine
{
    // manages 
    class  SceneManager: public ISystem
    {
    ASENGINE_DEFINE_SINGLETON(SceneManager);

    public:
        // change scene to other scene
        void ChangeSceneTo(ResourceRef<Scene> scene);

        // reload current scene
        void ReloadCurrentScene();

    private:
        ResourceRef<Scene> m_CurrentScene = ResourceRef<Scene>::NONE();
    
        void Init() override;
    };
} // namespace ASEngine

#endif // __ASENGINE_SCENE_MANAGER_H
