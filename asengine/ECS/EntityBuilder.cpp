#include "EntityBuilder.h"
#include "ComponentManager.h"
#include "ArchetypeManager.h"


#include "Core/Serialization/Json.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{
    EntityBuilder::EntityBuilder(const EntityBuilder &builder)
    {
        for (auto& [componentName, component]: builder.m_Components)
        {
            AddComponent(componentName, *component);
        }
    }

    EntityBuilder &EntityBuilder::operator=(const EntityBuilder &builder)
    {
        for (auto &[componentName, component] : builder.m_Components)
        {
            AddComponent(componentName, *component);
        }
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
        for (auto &component : object.items())
        {
            UniqueString componentName{ component.key() };
            dest.AddComponent(componentName);
            dest.GetComponent(componentName).Deserialize(component.value());
        }
    }

} // namespace ASEngine
