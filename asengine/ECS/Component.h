#ifndef __ASENGINE_COMPONENT_H
#define __ASENGINE_COMPONENT_H

#include <cstdint>

#include "Macros/Foreach.h"

#include "Class/Object.h"
#include "Class/Class.h"

#include "Core/Serialization/Serializer.h"
#include "Core/String/UniqueString.h"
#include "Core/Error/Assertion.h"

#include "Entity.h"



namespace ASEngine
{
    // abstract  component
    class  AbstractComponent : public Object
    {
    public:
        virtual ~AbstractComponent() {};

        // only to initialize some internal values. Avoid using it like unity's monobehaviour
        // entityID is passed as a parameter
        virtual void OnCreate(EntityID entityID) = 0;

        // used to manage internal values at destruction. Avoid using it like unity's monobehaviour
        virtual void OnDestroy() = 0;

        // copy component
        virtual void Copy(const AbstractComponent& component) = 0;

        // deserialize component
        virtual void Deserialize(const Json& object) = 0;

        // serialize component
        virtual Json Serialize() = 0;
    };

    // component
    template <typename T>
    class Component : public AbstractComponent
    {
    ASENGINE_DEFINE_CLASS(T);

    public:
        ~Component() {};

        // usefull for copying components from EntityBuilder to Archetype
        void Copy(const AbstractComponent& component) override
        {
            const T* castedSrc = static_cast<const T*>(&component);
            T* castedDest = static_cast<T*>(this);
            // ASENGINE_ASSERT(castedSrc, "Component Source Invalid Type");

            *castedDest = *castedSrc;
        }

        Json Serialize() override
        {
            return Serializer::Serialize(dynamic_cast<T&>(*this));
        }

        void Deserialize(const Json& object) override
        {
            Serializer::Deserialize(object, dynamic_cast<T&>(*this));
        }
    };
}

// export no field
#define  ASENGINE_EXPORT_EMPTY(ComponentType) \
    template <> \
    Json  Serializer::Serialize(const ComponentType &value) \
    { \
        return Json({}); \
    } \
    template <> \
    void  Serializer::Deserialize(const Json &object, ComponentType &dest) \
    { \
    }

// export component field to be serialiazed/deserialized
#define ASENGINE_EXPORT(ComponentType, ...) template <> \
    Json  Serializer::Serialize(const ComponentType &value) { \
        Json object = Json({}); \
        FOREACH(SERIALIZE_FIELD,  __VA_ARGS__) \
        return object; \
    } \
    template <> \
    void  Serializer::Deserialize(const Json &object, ComponentType &dest) \
    { \
        ASENGINE_ASSERT(object.is_object(), ""); \
        FOREACH(DESERIALIZE_FIELD,  __VA_ARGS__) \
    }

#define SERIALIZE_FIELD(field) \
    object[#field] = Serializer::Serialize(value.field);

#define DESERIALIZE_FIELD(field) \
    Serializer::Deserialize(object.at(#field), dest.field);


#endif
