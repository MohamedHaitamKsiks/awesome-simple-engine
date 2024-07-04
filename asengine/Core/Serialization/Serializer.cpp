#include "Serializer.h"
#include "Core/Error/Assertion.h"

namespace ASEngine
{
    // defined implementation for basic types
    // int
    template<> 
    Json Serializer::Serialize(const int &value)
    {
        return Json(value);
    }
    template <>
    void Serializer::Deserialize(const Json &object, int& dest)
    {
        ASENGINE_ASSERT(object.is_number_integer(), "Can't deserialize int if Json object is not an integer number");
        dest = object.get<int>();
    }

    // uint32_t
    template <>
    Json Serializer::Serialize(const uint32_t &value)
    {
        return Json(value);
    }
    template <>
    void Serializer::Deserialize(const Json &object, uint32_t &dest)
    {
        ASENGINE_ASSERT(object.is_number_integer(), "Can't deserialize int if Json object is not an integer number");
        dest = object.get<uint32_t>();
    }

    // float
    template <>
    Json Serializer::Serialize(const float &value)
    {
        return Json(value);
    }
    template <>
    void Serializer::Deserialize(const Json &object, float& dest)
    {
        ASENGINE_ASSERT(object.is_number(), "Can't deserialize float if Json object is not a number");
        dest = object.get<float>();
    }

    // boolean
    template <>
    Json Serializer::Serialize(const bool &value)
    {
        return Json(value);
    }
    template <> 
    void Serializer::Deserialize(const Json &object, bool &dest)
    {
        ASENGINE_ASSERT(object.is_boolean(), "Can't deserialize bool if Json object is not a boolean");
        dest = object.get<bool>();
    }

    // std::string
    template <>
    Json Serializer::Serialize(const std::string &value)
    {
        return Json(value);
    }
    template <>
    void Serializer::Deserialize(const Json &object, std::string &dest)
    {
        ASENGINE_ASSERT(object.is_string(), "Can't deserialize std::string if Json object is not a string");
        dest = object.get<std::string>();
    }


} // namespace ASEngine
