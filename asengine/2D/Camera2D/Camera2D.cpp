#include "Camera2D.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{
    template<>
    Json Serializer::Serialize(const Camera2D& camera2D)
    {
        return Json({});
    }

    template<>
    void Serializer::Deserialize(const Json& object, Camera2D& camera2D)
    {
        if (object.find("Target") != object.end())
            Serializer::Deserialize(object.at("Target"), camera2D.Target);

        std::vector<UniqueString> layerNames{};
        Serializer::Deserialize(object.at("Layers"), layerNames);

        for (auto& layerName: layerNames)
        {
            camera2D.Layers.insert(layerName);
        }
    }

    void Camera2D::OnCreate(EntityID entityID)
    {
    }

    void Camera2D::OnDestroy()
    {
    }
} // namespace ASEngine
