#ifndef __ASENGINE_RESOURCE_REF_SERIALIAZATION_H
#define __ASENGINE_RESOURCE_REF_SERIALIAZATION_H

#include <string>

#include "ResourceRef.h"
#include "Resource.h"
#include "IResourceClass.h"

#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Core/String/UniqueString.h"

// define serialization
/*
Example of loading resource path:
    ...
    resource: "materials/default.mat.json",
    ...

Example of inline definition
    ...
    resource: {
        "Shader": "shaders/default.shader.json",
        "VertexInput ....
    }
    ...
*/
#define ASENGINE_SERIALIZE_RESOURCE_REF(Type) \
namespace ASEngine \
{ \
    template<> \
    void Serializer::Deserialize(const Json &object, ResourceRef<Type> &dest) \
    { \
        if (object.is_string()) \
        { \
            UniqueString resourcePath; \
            Serializer::Deserialize(object, resourcePath); \
            ResourceRef<Resource> resource = Type::GetResourceClass().Load(resourcePath); \
            dest = ResourceRef<Type>(resource); \
        } \
        else \
        { \
            ResourceRef<Resource> resource = Type::GetResourceClass().New(); \
            resource->Deserialize(object); \
            dest = ResourceRef<Type>(resource); \
        } \
        \
    } \
    \
    template <> \
    Json  Serializer::Serialize(const ResourceRef<Type> &dest) \
    { \
        return Json(); \
    } \
}

#endif // __ASENGINE_RESOURCE_REF_SERIALIAZATION_H
