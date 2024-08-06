#include "EntityBuilder.h"
#include "ComponentManager.h"
#include "ArchetypeManager.h"


#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{
    void EntityBuilder::Copy(const EntityBuilder& builder)
    {
        for (auto& [componentName, component]: builder.m_Components)
        {
            AddComponent(componentName, *component);
        }
        SetTag(builder.GetTag());
        SetPersistant(builder.IsPersistant());
    }

    EntityBuilder::EntityBuilder(const EntityBuilder &builder)
    {
        Copy(builder);
    }

    EntityBuilder &EntityBuilder::operator=(const EntityBuilder &builder)
    {
        Copy(builder);
        return *this;
    }

    void EntityBuilder::AddComponent(UniqueString componentName)
    {
        IComponentClass& componentClass = ComponentManager::GetInstance().GetComponentClass(componentName);
        std::unique_ptr<AbstractComponent> newComponent(componentClass.New());

        // add component
        m_Components[componentName] = std::move(newComponent);
        m_Signature.emplace(componentName);

        // get currrent archetype
        m_Archetype = &ArchetypeManager::GetInstance().GetArchetype(m_Signature);
    }

    void EntityBuilder::AddComponent(UniqueString componentName, const AbstractComponent &component)
    {
        AddComponent(componentName);
        m_Components[componentName]->Copy(component);
    }

    // serialization of Entity Builder
    template <>
    Json  Serializer::Serialize(const EntityBuilder &value)
    {
        Json object = Json({});
        // add later ...
        return object;
    }

    template <>
    void  Serializer::Deserialize(const Json &object, EntityBuilder &dest)
    {
        // tag
        const std::string tagString = "Tag";
        if (object.find(tagString) != object.end())
        {
            UniqueString tag (object.at(tagString).get<std::string>());
            dest.SetTag(tag);
        }

        // persistent
        const std::string isPeristentString = "IsPersistent";
        if (object.find(isPeristentString) != object.end())
        {
            bool isPersistent = object.at(isPeristentString).get<bool>();
            dest.SetPersistant(isPersistent);
        }

        // components
        const auto& components = object.at("Components");
        for (const auto &component : components.items())
        {
            UniqueString componentName(component.key());
            dest.AddComponent(componentName);
            dest.GetComponent(componentName).Deserialize(component.value());
        }
    }

} // namespace ASEngine
