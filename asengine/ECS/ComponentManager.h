#ifndef __ASENGINE_COMPONENT_MANAGER_H
#define __ASENGINE_COMPONENT_MANAGER_H

#include <memory>
#include <cstdint>
#include <type_traits>
#include <unordered_map>

#include "Core/Serialization/Serializer.h"
#include "Core/Singleton/Singleton.h"

#include "Class/ClassManager.h"

#include "Component.h"
#include "ComponentClass.h"
#include "ComponentCollection.h"
#include "Signature.h"



// register component type
#define ASENGINE_REGISTER_COMPONENT(component) ComponentManager::GetInstance().RegisterComponent<component>(UniqueString(#component))

namespace ASEngine
{
    // singleton that manages components
    class  ComponentManager
    {
    ASENGINE_DEFINE_SINGLETON(ComponentManager);
    public:
        // register component
        template <typename T>
        void RegisterComponent(UniqueString componentName)
        {
            static_assert(std::is_base_of_v<Component<T>, T>);
            // register component as class 
            ClassManager::GetInstance().RegisterClass<T>(componentName);

            // register component specific behavior
            std::unique_ptr<IComponentClass> componentClass = std::make_unique<ComponentClass<T>>();
            m_Components[componentName] = std::move(componentClass);
        }

        // get component class
        inline IComponentClass& GetComponentClass(UniqueString componentName)
        {
            return *m_Components[componentName];
        }

        // get signature
        template<typename T, typename... types>
        static void GetSignature(Signature& signature)
        {
            static_assert(std::is_base_of_v<Component<T>, T>);
            signature.emplace(Component<T>::GetName());

            if constexpr (sizeof...(types) > 0)
            {
                GetSignature<types...>(signature);
            }
        }

    private:
        // component infos
        std::unordered_map<UniqueString, std::unique_ptr<IComponentClass>> m_Components;
    };

} // namespace ASEngine


#endif