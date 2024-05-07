#include "EntityBuilder.h"
#include "ComponentManager.h"

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

    void EntityBuilder::AddComponent(UniqueString componentName)
    {
        ComponentClass& componentClass = ComponentManager::GetInstance().GetComponentClass(componentName);
        std::unique_ptr<IComponent> newComponent(componentClass.New());

        // add component
        m_Components[componentName] = std::move(newComponent);
        m_Signature.emplace(componentName);
    }

    void EntityBuilder::AddComponent(UniqueString componentName, const IComponent &component)
    {
        AddComponent(componentName);
        m_Components[componentName]->Copy(component);
    }

    // serialization of Entity Builder
    template <>
    Json Serializer<EntityBuilder>::Serialize(const EntityBuilder &value)
    {
        Json object = Json({});
        // add later ...
        return object;
    }

    template <>
    void Serializer<EntityBuilder>::Deserialize(const Json &object, EntityBuilder &dest)
    {
        for (auto &component : object.items())
        {
            UniqueString componentName{ component.key() };
            dest.AddComponent(componentName);
            dest.GetComponent(componentName).Deserialize(component.value());
        }
    }

} // namespace ASEngine
