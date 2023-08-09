#ifndef ASENGINE_COMPONENT_MANAGER_H
#define ASENGINE_COMPONENT_MANAGER_H

#include <memory>
#include <cstdint>
#include <type_traits>
#include <unordered_map>

#include "Component.h"
#include "engine/Singleton/Singleton.h"

namespace ASEngine
{
    // component collection vector for now
    template <typename T>
    using ComponentCollection = TDynamicArray<T>;
    using BaseComponentCollection = DynamicArray;

    // component information used by component manager
    struct ComponentInfo
    {
        UniqueString Name;
        uint32_t Signature;
        size_t Size = 0;
        std::shared_ptr<BaseComponentCollection> (*CreateComponentCollection)();
    };

    // singleton that manages components
    class ComponentManager: public Singleton<ComponentManager>
    {
    public:
        // register component
        template <typename T>
        static inline void RegisterComponent(UniqueString componentName) { GetSingleton()->IRegisterComponent<T>(componentName); };

        // create component collection
        template <typename T>
        static std::shared_ptr<BaseComponentCollection> CreateComponentCollection();

        // create component collection
        inline static std::shared_ptr<BaseComponentCollection> CreateComponentCollection(UniqueString componentName) { return GetSingleton()->ICreateComponentCollection(componentName); };

        // get signature of a composition of components
        template <typename T, typename... types>
        static uint32_t GetSignature();

        // get signature
        inline static uint32_t GetSignature(UniqueString componentName) { return GetSingleton()->IGetSignature(componentName); }

    private:
        template <typename T>
        void IRegisterComponent(UniqueString componentName);

        // is valid signature <===> is prime
        bool IsValidSignature(uint32_t signature);

        // create component collection
        std::shared_ptr<BaseComponentCollection> ICreateComponentCollection(UniqueString componentName);

        // get signature by name
        uint32_t IGetSignature(UniqueString componentName);

        // last component signature
        uint32_t m_LastComponentSignature = 1;

        // component infos
        std::unordered_map<UniqueString, ComponentInfo> m_Components;

    };

    // implementations

    // create component collection
    template <typename T>
    std::shared_ptr<BaseComponentCollection> ComponentManager::CreateComponentCollection()
    {
        return std::make_shared<ComponentCollection<T>>(UINT16_MAX);
    };

    // register component implementation
    template <typename T>
    void ComponentManager::IRegisterComponent(UniqueString componentName)
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);

        // create signature
        int currentNumber = m_LastComponentSignature + 1;
        for (uint32_t i = m_LastComponentSignature + 1; i < UINT32_MAX; i++)
        {
            if (IsValidSignature(i))
            {
                // register component
                Component<T>::s_Signature = i;
                Component<T>::s_Name = componentName;

                // add component info
                ComponentInfo info;
                info.Name = componentName;
                info.Signature = i;
                info.Size = sizeof(T);
                info.CreateComponentCollection = ComponentManager::CreateComponentCollection<T>;
                
                m_Components[componentName] = info;

                // update last component signature
                m_LastComponentSignature = i;
                return;
            }
        }
    };

    // get signature implementation
    template <typename T, typename... types>
    uint32_t ComponentManager::GetSignature()
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);

        // compute signature
        uint32_t signature = Component<T>::s_Signature;
        if constexpr (sizeof...(types) > 0)
        {
            signature *= GetSignature<types...>();
        }

        return signature;
    };

} // namespace ASEngine


#endif