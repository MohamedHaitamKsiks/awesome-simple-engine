#include "Scene.h"

#include "Resource/ResourceRefSerialization.h"
#include "ECS/EntityManager.h"


ASENGINE_SERIALIZE_RESOURCE_REF(Scene);

namespace ASEngine
{
    template<>
    void Serializer::Deserialize(const Json& object, Scene& dest)
    {
        std::vector<EntityBuilder> builders = {};
        Serializer::Deserialize(object.at("Entities"), builders);

        dest.Create(builders);
    }

    template <>
    Json Serializer::Serialize(const Scene &scene)
    {
        Json sceneObject = Json({});
        sceneObject["Entities"] = Serializer::Serialize(scene.m_Builders);
    
        return sceneObject;
    }

    ASENGINE_SERIALIZE_RESOURCE_IMP(Scene);

    void Scene::Create(const std::vector<EntityBuilder> &builders)
    {
        m_Builders.reserve(builders.size());
        
        for (const auto& builder: builders)
        {
            m_Builders.push_back(builder);
        }
    }

    void Scene::Instanciate()
    {
        for (auto& builder: m_Builders)
        {
            EntityManager::GetInstance().Create(builder);
        }
    }

} // namespace ASEngine
