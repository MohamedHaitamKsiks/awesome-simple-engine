#ifndef ASENGINE_COMPONENT_MANAGER_H
#define ASENGINE_COMPONENT_MANAGER_H

#include <memory>
#include <cstdint>
#include <type_traits>
#include <unordered_map>

#include "Core/Serialization/Serializer.h"
#include "Core/Singleton/Singleton.h"

#include "Object/ClassManager.h"

#include "Component.h"
#include "ComponentClass.h"
#include "ComponentCollection.h"
#include "Signature.h"

#include "System.h"

namespace ASEngine
{

    // singleton that manages components
    class ComponentManager: public ISystem, public Singleton<ComponentManager>
    {
    public:
        // register component
        template <typename T>
        void RegisterComponent(UniqueString componentName)
        {
            static_assert(std::is_base_of_v<Component<T>, T>);
            // register component as class 
            ClassManager::GetInstance().RegisterClass<T>(componentName);

            // register component specific behavior
            std::unique_ptr<ComponentClass> componentClass = std::make_unique<TComponentClass<T>>(componentName);
            m_Components[componentName] = std::move(componentClass);
        }

        // get component class
        inline ComponentClass& GetComponentClass(UniqueString componentName)
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
        std::unordered_map<UniqueString, std::unique_ptr<ComponentClass>> m_Components;
    };

} // namespace ASEngine


#endif