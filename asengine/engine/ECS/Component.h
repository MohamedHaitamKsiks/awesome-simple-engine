#ifndef ASENGINE_COMPONENT_H
#define ASENGINE_COMPONENT_H

#include <cstdint>

#include "Macros/Foreach.h"

#include "Core/Serialization/Serializer.h"
#include "Core/String/UniqueString.h"

#include "Entity.h" 

namespace ASEngine
{
    // base component type
    struct Component
    {
        // entity owner
        Entity Owner = CHUNK_NULL;

        Component() = default;
        ~Component() = default;

        // only to initialize some internal values. Avoid using it like unity's monobehaviour
        virtual void OnCreate() {};

        // used to manage internal values at destruction. Avoid using it like unity's monobehaviour
        virtual void OnDestroy() {};
    };

    // component
    template <typename T>
    struct TComponent: Component
    {
        // component name
        static UniqueString s_Name;

    };

    // component name implementation
    template <typename T>
    UniqueString TComponent<T>::s_Name = CHUNK_NULL;

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