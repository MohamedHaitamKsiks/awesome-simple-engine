#ifndef ASENGINE_COMPONENT_H
#define ASENGINE_COMPONENT_H

#include <cstdint>

#include "Macros/Foreach.h"

#include "Class/Class.h"

#include "Core/Serialization/Serializer.h"
#include "Core/String/UniqueString.h"
#include "Core/Error/Assertion.h"

#include "Entity.h" 

namespace ASEngine
{
    // interface for component 
    class IComponent
    {
    public:
        virtual ~IComponent() {};

        // only to initialize some internal values. Avoid using it like unity's monobehaviour
        // entityID is passed as a parameter
        virtual void OnCreate(EntityID entityID) = 0;

        // used to manage internal values at destruction. Avoid using it like unity's monobehaviour
        virtual void OnDestroy() = 0;
    
        // copy component
        virtual void Copy(const IComponent& component) = 0;

        // deserialize component
        virtual void Deserialize(const Json& object) = 0;

        // serialize component
        virtual Json Serialize() = 0;
    };

    // component
    template <typename T>
    class Component : public IComponent 
    {
    ASENGINE_DEFINE_CLASS(T);

    public:
        ~Component() {};

        // usefull for copying components from EntityBuilder to Archetype
        void Copy(const IComponent& component) override
        {
            const T* castedSrc = dynamic_cast<const T*>(&component);
            T* castedDest = dynamic_cast<T*>(this);
            ASENGINE_ASSERT(castedSrc, "Component Source Invalid Type");

            *castedDest = *castedSrc;
        }

        Json Serialize() override
        {
            return Serializer<T>::Serialize(dynamic_cast<T&>(*this));
        }

        void Deserialize(const Json& object) override
        {
            Serializer<T>::Deserialize(object, dynamic_cast<T&>(*this));
        }
    };  
}

// export no field
#define ASENGINE_EXPORT_EMPTY(ComponentType) \
    template <> \
    Json Serializer<ComponentType>::Serialize(const ComponentType &value) \
    { \
        return Json({}); \
    } \
    template <> \
    void Serializer<ComponentType>::Deserialize(const Json &object, ComponentType &dest) \
    { \
    }

// export component field to be serialiazed/deserialized
#define ASENGINE_EXPORT(ComponentType, ...) template <> \
    Json Serializer<ComponentType>::Serialize(const ComponentType &value) { \
        Json object = Json({}); \
        FOREACH(SERIALIZE_FIELD,  __VA_ARGS__) \
        return object; \
    } \
    template <> \
    void Serializer<ComponentType>::Deserialize(const Json &object, ComponentType &dest) \
    { \
        ASENGINE_ASSERT(object.is_object(), ""); \
        FOREACH(DESERIALIZE_FIELD,  __VA_ARGS__) \
    } 

#define SERIALIZE_FIELD(field) \
    object[#field] = Serializer<decltype(value.field)>::Serialize(value.field); 

#define DESERIALIZE_FIELD(field) \
    Serializer<decltype(dest.field)>::Deserialize(object.at(#field), dest.field);


#endif