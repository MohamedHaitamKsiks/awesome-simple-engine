#ifndef ASENGINE_RESOURCE_REF_SERIALIAZATION_H
#define ASENGINE_RESOURCE_REF_SERIALIAZATION_H

#include <string>

#include "ResourceRef.h"
#include "AbstractResource.h"
#include "IResourceClass.h"

#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"
#include "Core/String/UniqueString.h"

// define serialization
/*
Example:
    ...
    resource: "materials/default.mat.json",
    ...
*/
#define ASENGINE_SERIALIZE_RESOURCE_REF(Type) \
namespace ASEngine \
{ \
    template<> \
    void Serializer<ResourceRef<Type>>::Deserialize(const Json &object, ResourceRef<Type> &dest) \
    { \
        UniqueString resourcePath; \
        Serializer<UniqueString>::Deserialize(object, resourcePath); \
        \
        ResourceRef<AbstractResource> resource = Type::GetResourceClass().GetResource(resourcePath); \
        dest = ResourceRef<Type>(resource); \
    } \
    \
    template <> \
    Json Serializer<ResourceRef<Type>>::Serialize(const ResourceRef<Type> &dest) \
    { \
        return Json(dest->GetReferenceName().GetString()); \
    } \
}

#endif // ASENGINE_RESOURCE_REF_SERIALIAZATION_H