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
            EntityBuilder builder;
            Serializer<EntityBuilder>::Deserialize(entity, builder);
            dest.AddEntityBuilder(builder);
        }
    }

    bool Scene::Load(const std::string &path)
    {
        // open scene file
        File sceneFile;
        if (!sceneFile.Open(path, FileOpenMode::READ))
            return false;
        auto sceneText = sceneFile.ReadText();
        sceneFile.Close();

        // deserialize scene
        Json sceneObject = Json::parse(sceneText);
        Serializer<Scene>::Deserialize(sceneObject, *this);

        return true;
    }

} // ASEngine