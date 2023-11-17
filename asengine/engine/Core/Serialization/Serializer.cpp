#include "Serializer.h"

#include "Core/String/UniqueString.h"
#include "Core/Math/vec2.h"
#include "Renderer/Color.h"
#include "ECS/EntityBuilder.h"

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
        dest = std::string(object);
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
        assert(object.is_object());
        
        Serializer<float>::Deserialize(object.at("r"), dest.r);
        Serializer<float>::Deserialize(object.at("g"), dest.g);
        Serializer<float>::Deserialize(object.at("b"), dest.b);
        Serializer<float>::Deserialize(object.at("a"), dest.a);
    }

    // Entity Builder
    template <>
    Json Serializer<EntityBuilder>::Serialize(const EntityBuilder &value)
    {
        Json object = Json({});
        // add later ...
        return object;
    }
    template <>
    void Serializer<EntityBuilder>::Deserialize(const Json &object, EntityBuilder &dest)
    {
        assert(object.is_object());
        for (auto &component : object.items())
        {
            UniqueString componentName = UniqueString(component.key());

            Component *componentValue = ComponentManager::MakeComponent(componentName, nullptr);
            ComponentManager::Deserialize(componentName, component.value(), componentValue);

            dest.AddComponent(componentName, componentValue);

            ComponentManager::DeleteComponent(componentName, componentValue);
        }
    }

} // namespace ASEngine
