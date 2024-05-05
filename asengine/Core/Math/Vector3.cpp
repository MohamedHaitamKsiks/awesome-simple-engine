#include "Vector3.h"

namespace ASEngine
{

    // serialization of Vector3
    template <>
    Json Serializer<Vector3>::Serialize(const Vector3 &value)
    {
        Json vector3Obj{{}};
        vector3Obj["x"] = value.x;
        vector3Obj["y"] = value.y;
        vector3Obj["z"] = value.z;

        return vector3Obj;
    }
    template <>
    void Serializer<Vector3>::Deserialize(const Json &object, Vector3 &dest)
    {
        ASENGINE_ASSERT(object.is_object(), "Can't deserialize Vector3 if it's not an object");
        Serializer<float>::Deserialize(object.at("x"), dest.x);
        Serializer<float>::Deserialize(object.at("y"), dest.y);
        Serializer<float>::Deserialize(object.at("z"), dest.z);
    }
} // namespace ASEngine
