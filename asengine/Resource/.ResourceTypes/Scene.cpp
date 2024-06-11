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
            EntityManager::Create(builder);
        }
    }

    void Scene::ChangeSceneTo(Scene &scene)
    {
        EntityManager::DestroyAll();
        scene.Instantiate();
    };

    // seriliazation
    template <>
    Json Serializer::Serialize(const Scene &value)
    {
        Json object = Json({});
        return object;
    }
    template <>
    void Serializer::Deserialize(const Json &object, Scene &dest)
    {
        assert(object.is_array());
        
        for(auto& entity: object)
        {
            EntityBuilder builder;
            Serializer::Deserialize(entity, builder);
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
        Serializer::Deserialize(sceneObject, *this);

        return true;
    }

} // ASEngine