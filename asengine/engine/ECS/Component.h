#ifndef ASENGINE_COMPONENT_H
#define ASENGINE_COMPONENT_H

#include <cstdint>
#include "engine/Macros/Foreach.h"

#include "engine/Serialization/Serializer.h"
#include "engine/String/UniqueString.h"
#include "Entity.h" 

namespace ASEngine
{
    // base component type
    struct Component
    {
        Component() = default;
        ~Component() = default;

        // only to initialize some internal values. Avoid using it like unity's monobehaviour
        virtual void OnCreate() {};
    };

    // component
    template <typename T>
    struct TComponent: Component
    {
        // component name
        static UniqueString s_Name;

        // component signature
        static uint32_t s_Signature;
    };

    // component name implementation
    template <typename T>
    UniqueString TComponent<T>::s_Name = CHUNK_NULL;

    // component signature
    template <typename T>
    uint32_t TComponent<T>::s_Signature = 0;

}

// export component field to be serialiazed/deserialized
#define EXPORT(ComponentType, ...) template <> \
    Json Serializer<ComponentType>::Serialize(const ComponentType &value) { \
        Json object = Json({}); \
        return object; \
    } \
    template <> \
    void Serializer<ComponentType>::Deserialize(const Json &object, ComponentType &dest) \
    { \
        assert(object.is_object()); \
        FOREACH(DESERIALIZE_FIELD,  __VA_ARGS__) \
    } 

#define SERIALIZE_FIELD(field) \
    object[#field] = Serializer<decltype(value.field)>::Serialize(value.field); 

#define DESERIALIZE_FIELD(field) \
    Serializer<decltype(dest.field)>::Deserialize(object.at(#field), dest.field);


#endif