#ifndef __ASENGINE_RESOURCE_SERIALIAZATION_H
#define __ASENGINE_RESOURCE_SERIALIAZATION_H



#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

// serialize resource type (DO NOT SERIALIZE TO STRING BECAUSE IT MIGHT TRY TO LOAD IT AS A PATH)
#define ASENGINE_SERIALIZE_RESOURCE(T) \
public: \
    void Deserialize(const Json &object) override; \
    Json Serialize() const override

// implemente resource serialiazation
#define ASENGINE_SERIALIZE_RESOURCE_IMP(T) \
void T::Deserialize(const Json &object) \
{ \
    Serializer::Deserialize(object, static_cast<T&>(*this)); \
} \
\
Json T::Serialize() const \
{ \
    return Serializer::Serialize(static_cast<const T&>(*this)); \
}

#endif // __ASENGINE_RESOURCE_SERIALIAZATION_H