#include "Vector3.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Serialization/Json.h"

namespace ASEngine
{

    // serialization of Vector3
    template <>
    Json Serializer::Serialize(const Vector3 &value)
    {
        Json vector3Obj = Json({});
        vector3Obj["x"] = value.x;
        vector3Obj["y"] = value.y;
        vector3Obj["z"] = value.z;

        return vector3Obj;
    }

    template <>
    void Serializer::Deserialize(const Json &object, Vector3 &dest)
    {
        ASENGINE_ASSERT(object.is_object(), "Can't deserialize Vector3 if it's not an object");
        Serializer::Deserialize(object.at("x"), dest.x);
        Serializer::Deserialize(object.at("y"), dest.y);
        Serializer::Deserialize(object.at("z"), dest.z);
    }
} // namespace ASEngine
