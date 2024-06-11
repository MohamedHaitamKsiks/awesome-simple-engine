#ifndef __ASENGINE_SERIALIZE_STRUCT_H
#define __ASENGINE_SERIALIZE_STRUCT_H

#include "Macros/Foreach.h"

#include "Core/Serialization/Serializer.h"
#include "Core/String/UniqueString.h"

#define ASENGINE_SERIALIZE_STRUCT_FIELD(dest, field) \
    object[#field] = Serializer::Serialize(value.field);

#define ASENGINE_DESERIALIZE_STRUCT_FIELD(dest, field) \
    Serializer::Deserialize(object.at(#field), dest.field);

#define __SERIALIZE_STRUCT_FIELD(field) ASENGINE_SERIALIZE_STRUCT_FIELD(dest, field)
#define __DESERIALIZE_STRUCT_FIELD(field) ASENGINE_DESERIALIZE_STRUCT_FIELD(dest, field)

// serialize struct by exporting no filed <=> Json({})
#define ASENGINE_SERIALIZE_STRUCT_EMPTY(StructType) \
    template <> \
    Json Serializer::Serialize(const StructType &value) \
    { \
        return Json({}); \
    } \
    template <> \
    void Serializer::Deserialize(const Json &object, StructType &dest) \
    { \
    }

// serialze struct by exprting fields as Json object
#define ASENGINE_SERIALIZE_STRUCT(StructType, ...) template <> \
    Json Serializer::Serialize(const StructType &value) { \
        Json object = Json({}); \
        FOREACH(__SERIALIZE_STRUCT_FIELD,  __VA_ARGS__) \
        return object; \
    } \
    template <> \
    void Serializer::Deserialize(const Json &object, StructType &dest) \
    { \
        ASENGINE_ASSERT(object.is_object(), ""); \
        FOREACH(__DESERIALIZE_STRUCT_FIELD,  __VA_ARGS__) \
    } 


#endif // __ASENGINE_SERIALIZE_STRUCT_H