

#include "Scene.h"

namespace ASEngine 
{
    bool Scene::Load(TDynamicArray<EntityBuilder> &builders)
    {
        m_Builders.Clear();
        for (auto& builder: builders)
        {
            m_Builders.Push(builder);
        }
        return true;
    }

    void Scene::AddEntityBuilder(const EntityBuilder &builder)
    {
        m_Builders.Push(builder);
    }

    void Scene::Instantiate()
    {
        for (auto &builder : m_Builders)
        {
            World::Create(builder);
        }
    }

    void Scene::ChangeSceneTo(Scene &scene)
    {
        World::DestroyAll();
        scene.Instantiate();
    };

    // seriliazation
    template <>
    Json Serializer<Scene>::Serialize(const Scene &value)
    {
        Json object = Json({});
        return object;
    }
    template <>
    void Serializer<Scene>::Deserialize(const Json &object, Scene &dest)
    {
        assert(object.is_array());
        
        for(auto& entity: object)
        {
            assert(entity.is_object());

            EntityBuilder builder;
            for (auto& component: entity.items())
            {
                UniqueString componentName = UniqueString(component.key());

                std::unique_ptr<Component> componentValue(ComponentManager::MakeComponent(componentName, nullptr));
                ComponentManager::Deserialize(componentName, component.value(), componentValue.get());

                builder.AddComponent(componentName, componentValue.get());
            }

            dest.AddEntityBuilder(builder);

        }

    }

} // ASEngine