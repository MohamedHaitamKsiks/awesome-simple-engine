#ifndef ASENGINE_COMPONENT_H
#define ASENGINE_COMPONENT_H

#include <cstdint>

#include "Macros/Foreach.h"

#include "Core/Serialization/Serializer.h"
#include "Core/String/UniqueString.h"
#include "Core/Error/Assertion.h"

#include "Entity.h" 

namespace ASEngine
{
    // base component type
    class Component
    {
    public:
        Component() = default;
        ~Component() = default;

        // only to initialize some internal values. Avoid using it like unity's monobehaviour
        virtual void OnCreate() {};

        // used to manage internal values at destruction. Avoid using it like unity's monobehaviour
        virtual void OnDestroy() {};

        // get component name
        virtual UniqueString GetName() const = 0;
    
        // copy component
        virtual void Copy(const Component& component) = 0;

        // deserialize component
        virtual void Deserialize(const Json& object) = 0;

        // serialize component
        virtual Json Serialize() = 0;

    private:
        EntityID m_OwnerID;
    };

    // component
    template <typename T>
    class TComponent: public Component
    {
    public:
        UniqueString GetName() const override
        {
            return s_Name;
        }

        static UniqueString GetComponentName()
        {
            return s_Name;
        }

        // usefull for copying components from EntityBuilder to Archetype
        void Copy(const Component& component)
        {
            const T* castedSrc = dynamic_cast<const T*>(&component);
            ASENGINE_ASSERT(castedSrc, "Component Source Invalid Type");

            *this = *castedSrc;
        }

        Json Serialize() override
        {
            return Serializer<T>::Serialize(*this);
        }

        void Deserialize(const Json& object) override
        {
            Serializer<T>::Deserialize(object, *this);
        }

    private:
        // component name
        static UniqueString s_Name;
        friend class ComponentManager;
    };  

    // component name implementation
    template <typename T>
    UniqueString TComponent<T>::s_Name{""};
}

// export no field
#define EXPORT_EMPTY(ComponentType) \
    template <> \
    Json Serializer<ComponentType>::Serialize(const ComponentType &value) \
    { \
        Json object = Json({}); \
        return object; \
    } \
    template <> \
    void Serializer<ComponentType>::Deserialize(const Json &object, ComponentType &dest) \
    { \
        ASENGINE_ASSERT(object.is_object(), ""); \
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
        ASENGINE_ASSERT(object.is_object(), ""); \
        FOREACH(DESERIALIZE_FIELD,  __VA_ARGS__) \
    } 

#define SERIALIZE_FIELD(field) \
    object[#field] = Serializer<decltype(value.field)>::Serialize(value.field); 

#define DESERIALIZE_FIELD(field) \
    Serializer<decltype(dest.field)>::Deserialize(object.at(#field), dest.field);


#endif