#include "Vector2.h"
#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{

    // rotate
    Vector2 Vector2::Rotate(float angle) const
    {
        float cosAngle = Math::Cos(angle);
        float sinAngle = Math::Sin(angle);

        return Vector2
        {
            x * cosAngle - y * sinAngle,
            x * sinAngle + y * cosAngle
        };
    }

    // serialization of vector2
    template <>
    Json Serializer::Serialize(const Vector2 &value)
    {
        Json vector2Obj = Json({});
        vector2Obj["x"] = value.x;
        vector2Obj["y"] = value.y;

        return vector2Obj;
    }

    template <>
    void Serializer::Deserialize(const Json &object, Vector2 &dest)
    {
        ASENGINE_ASSERT(object.is_object(), "Can't deserialize Vecto2 if it's not an object");
        Serializer::Deserialize(object.at("x"), dest.x);
        Serializer::Deserialize(object.at("y"), dest.y);
    }

} // namespace ASEngine
