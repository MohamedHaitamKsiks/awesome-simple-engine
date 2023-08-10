#include "Serializer.h"

namespace ASEngine
{
    // defined implementation for known serializable types

    // int
    template<> 
    Json Serializer<int>::Serialize(const int &value)
    {
        return Json(value);
    }
    template <>
    void Serializer<int>::Deserialize(const Json &object, int& dest)
    {
        assert(object.is_number_integer());
        dest = object;
    }

    // float
    template <>
    Json Serializer<float>::Serialize(const float &value)
    {
        return Json(value);
    }
    template <>
    void Serializer<float>::Deserialize(const Json &object, float& dest)
    {
        assert(object.is_number());
        dest = (float) object;
    }

    // boolean
    template <>
    Json Serializer<bool>::Serialize(const bool &value)
    {
        return Json(value);
    }
    template <> 
    void Serializer<bool>::Deserialize(const Json &object, bool &dest)
    {
        assert(object.is_boolean());
        dest = object;
    }

    // string
    template <>
    Json Serializer<std::string>::Serialize(const std::string &value)
    {
        return Json(value);
    }
    template <>
    void Serializer<std::string>::Deserialize(const Json &object, std::string &dest)
    {
        assert(object.is_string());
        dest = object;
    }

    // UniqueString
    template <>
    Json Serializer<UniqueString>::Serialize(const UniqueString &value)
    {
        return Json(value.GetString());
    }
    template <>
    void Serializer<UniqueString>::Deserialize(const Json &object,UniqueString &dest)
    {
        assert(object.is_string());
        dest = UniqueString(std::string(object));
    }

    // Vector2D
    template <>
    Json Serializer<vec2>::Serialize(const vec2 &value)
    {
        Json vector2DObject = Json({});
        vector2DObject["x"] = value.x;
        vector2DObject["y"] = value.y;

        return vector2DObject;
    }
    template <>
    void Serializer<vec2>::Deserialize(const Json &object, vec2&dest)
    {
        assert(object.is_object());
        Serializer<float>::Deserialize(object.at("x"), dest.x);
        Serializer<float>::Deserialize(object.at("y"), dest.y);
    }

} // namespace ASEngine
