#ifndef ASENGINE_COMPONENT_MANAGER_H
#define ASENGINE_COMPONENT_MANAGER_H

#include <memory>
#include <cstdint>
#include <type_traits>
#include <unordered_map>

#include "Core/Serialization/Serializer.h"
#include "Core/Singleton/Singleton.h"

#include "Component.h"
#include "ComponentCollection.h"
#include "Signature.h"

#include "System.h"


namespace ASEngine
{

    // component information used by component manager
    struct ComponentInfo
    {
        UniqueString Name;
        size_t Size = 0;
        std::function<IComponentCollection*()> CreateComponentCollection;
        std::function<Component*()> MakeComponent;
    };

    // singleton that manages components
    class ComponentManager: public ISystem, public Singleton<ComponentManager>
    {
    public:
        // register component
        template <typename T>
        void RegisterComponent(UniqueString componentName);

        // create component collection
        inline IComponentCollection* CreateComponentCollection(UniqueString componentName) 
        {
            return m_Components[componentName].CreateComponentCollection();
        };

        // make component by name
        inline Component* MakeComponent(UniqueString componentName)
        {
            return m_Components[componentName].MakeComponent();
        }

        // get size of a component
        inline size_t GetSize(UniqueString componentName) 
        { 
            return m_Components[componentName].Size; 
        }

        // get signature
        template<typename T, typename... types>
        static void GetSignature(Signature& signature)
        {
            static_assert(std::is_base_of_v<TComponent<T>, T>);
            signature.emplace(T::s_Name);

            if constexpr (sizeof...(types) > 0)
            {
                GetSignature<types...>(signature);
            }
        }

    private:
        // component infos
        std::unordered_map<UniqueString, ComponentInfo> m_Components;
    };

    // implementations

    // register component implementation
    template <typename ComponentType>
    void ComponentManager::RegisterComponent(UniqueString componentName)
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<TComponent<ComponentType>, ComponentType>);

        // register component
        TComponent<ComponentType>::s_Name = componentName;

        // add component info
        ComponentInfo info;
        info.Name = componentName;
        info.Size = sizeof(ComponentType);

        // define functions
        info.CreateComponentCollection = []()
        {
            IComponentCollection *collection = new ComponentCollection<ComponentType>();
            return collection;
        };

        info.MakeComponent = []()
        {
            return new ComponentType();
        };

        // add component info
        m_Components[componentName] = info;
    };


} // namespace ASEngine


#endif