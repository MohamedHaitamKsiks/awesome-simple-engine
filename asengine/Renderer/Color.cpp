#include "Color.h"

#include "Core/Error/Assertion.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{
    template <>
    Json Serializer<Color>::Serialize(const Color &value)
    {
        Json vector3Obj = Json({});
        vector3Obj["r"] = value.r;
        vector3Obj["g"] = value.g;
        vector3Obj["b"] = value.b;
        vector3Obj["a"] = value.a;

        return vector3Obj;
    }

    template <>
    void Serializer<Color>::Deserialize(const Json &object, Color &dest)
    {
        ASENGINE_ASSERT(object.is_object(), "Can't deserialize Color if it's not an object");
        Serializer<float>::Deserialize(object.at("r"), dest.r);
        Serializer<float>::Deserialize(object.at("g"), dest.g);
        Serializer<float>::Deserialize(object.at("b"), dest.b);
        Serializer<float>::Deserialize(object.at("a"), dest.a);
    }
} // namespace ASEngine
