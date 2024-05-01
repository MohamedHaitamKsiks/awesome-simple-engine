#include "Serializer.h"
#include "Core/Error/Assertion.h"

namespace ASEngine
{
    // defined implementation for basic types
    // int
    template<> 
    Json Serializer<int>::Serialize(const int &value)
    {
        return Json(value);
    }
    template <>
    void Serializer<int>::Deserialize(const Json &object, int& dest)
    {
        ASENGINE_ASSERT(object.is_number_integer(), "Can't deserialize int if Json object is not an integer number");
        dest = object.get<int>();
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
        ASENGINE_ASSERT(object.is_number(), "Can't deserialize float if Json object is not a number");
        dest = object.get<float>();
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
        ASENGINE_ASSERT(object.is_boolean(), "Can't deserialize bool if Json object is not a boolean");
        dest = object.get<bool>();
    }

    // std::string
    template <>
    Json Serializer<std::string>::Serialize(const std::string &value)
    {
        return Json(value);
    }
    template <>
    void Serializer<std::string>::Deserialize(const Json &object, std::string &dest)
    {
        ASENGINE_ASSERT(object.is_string(), "Can't deserialize std::string if Json object is not a string");
        dest = object.get<std::string>();
    }


    /*
    // Vector2D
    template <>
    Json Serializer<Vector2>::Serialize(const Vector2 &value)
    {
        Json vector2DObject = Json({});
        vector2DObject["x"] = value.x;
        vector2DObject["y"] = value.y;

        return vector2DObject;
    }
    template <>
    void Serializer<Vector2>::Deserialize(const Json &object, Vector2&dest)
    {
        assert(object.is_object());
        Serializer<float>::Deserialize(object.at("x"), dest.x);
        Serializer<float>::Deserialize(object.at("y"), dest.y);
    }

    // Color
    template <>
    Json Serializer<Color>::Serialize(const Color &value)
    {
        Json object = Json({});
        object["r"] = value.r;
        object["g"] = value.g;
        object["b"] = value.b;
        object["a"] = value.a;

        return object;
    }
    template <>
    void Serializer<Color>::Deserialize(const Json &object, Color &dest)
    {        
        Serializer<float>::Deserialize(object.at("r"), dest.r);
        Serializer<float>::Deserialize(object.at("g"), dest.g);
        Serializer<float>::Deserialize(object.at("b"), dest.b);
        Serializer<float>::Deserialize(object.at("a"), dest.a);
    }
    */

} // namespace ASEngine
