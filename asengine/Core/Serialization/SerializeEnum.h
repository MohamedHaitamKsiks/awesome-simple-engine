#ifndef __ASENGINE_SERIALIZE_ENUM_H
#define __ASENGINE_SERIALIZE_ENUM_H

#include <string>

#include "Serializer.h"
#include "Json.h"
#include "Macros/Foreach.h"

// serialize enum value
#define __DESERIALIZE_ENUM_VALUE(Value) \
else if (valueName == #Value) \
{ \
    dest = EnumType::Value; \
}

#define __SERIALIZE_ENUM_VALUE(Value) \
else if (src == EnumType::Value) \
{ \
    valueName = #Value; \
}

// serialize enums to string of the same name
#define ASENGINE_SERIALIZE_ENUM(Type, FirstValue, ...) \
template <>\
void Serializer::Deserialize(const Json &object, Type &dest) \
{ \
    using EnumType = Type; \
    std::string valueName = object.get<std::string>(); \
    if (valueName == #FirstValue) \
    { \
        dest = EnumType::FirstValue; \
    } \
    FOREACH(__DESERIALIZE_ENUM_VALUE, __VA_ARGS__) \
} \
template <>\
Json Serializer::Serialize(const Type &src) \
{ \
    using EnumType = Type; \
    std::string valueName = ""; \
    if (src == EnumType::FirstValue) \
    { \
        valueName = #FirstValue; \
    } \
    FOREACH(__SERIALIZE_ENUM_VALUE, __VA_ARGS__) \
    return Json(valueName); \
}

#endif // __ASENGINE_SERIALIZE_ENUM_H
