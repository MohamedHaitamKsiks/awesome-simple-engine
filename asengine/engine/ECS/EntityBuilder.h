#ifndef ASENGINE_ENTITY_BUILDER_H
#define ASENGINE_ENTITY_BUILDER_H

#include <memory>
#include <unordered_map>
#include <cstring>

#include "Core/Memory/DynamicArray.h"
#include "Core/String/UniqueString.h"

#include "Entity.h"
#include "Component.h"
#include "ComponentManager.h"

namespace ASEngine
{
    // builder to create a new entity 
    class EntityBuilder
    {
        public:
            // add component
            void AddComponent(UniqueString componentName, const Component* data);
            
            // add component based on type
            template <typename T, typename... types>
            void AddComponents(const T& firstComponent, const types&... components)
            {
                UniqueString componentName = TComponent<T>::s_Name;
                AddComponent(componentName, &firstComponent);

                if constexpr(sizeof...(types) > 0)
                {
                    AddComponents(components...);
                }
            }

        private:
            TDynamicArray<UniqueString> m_ComponentNames{};
            TDynamicArray<std::shared_ptr<Component>> m_Components{};
    
            // make world friend class
            friend class World;
    };

} // namespace ASEngine


#endif // ASENGINE_ENTITY_BUILDER_H