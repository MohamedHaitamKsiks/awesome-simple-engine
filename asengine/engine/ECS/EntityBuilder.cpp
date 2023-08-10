#include "EntityBuilder.h"

namespace ASEngine
{
    void EntityBuilder::AddComponent(UniqueString componentName, const Component *data)
    {
        m_ComponentNames.Push(componentName);
        Component* newComponent = ComponentManager::MakeComponent(componentName, data);
        m_Components.Push(std::shared_ptr<Component>(newComponent));

    }

} // namespace ASEngine
