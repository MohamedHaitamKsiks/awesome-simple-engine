#include "EntityBuilder.h"

namespace ASEngine
{
    EntityBuilder::~EntityBuilder()
    {
        for (int i = 0; i < m_ComponentNames.GetSize(); i++)
        {
            ComponentManager::DeleteComponent(m_ComponentNames[i], m_Components[i]);
        }
    }

    EntityBuilder::EntityBuilder(const EntityBuilder &builder)
    {
        for (int i = 0; i < builder.m_Components.GetSize(); i++)
        {
            auto componentName = builder.m_ComponentNames[i];
            auto* component = builder.m_Components[i];

            AddComponent(componentName, component);
        }
    }

    void EntityBuilder::AddComponent(UniqueString componentName, const Component *data)
    {
        m_ComponentNames.Push(componentName);
        Component* newComponent = ComponentManager::MakeComponent(componentName, data);
        m_Components.Push(newComponent);

    }

} // namespace ASEngine
