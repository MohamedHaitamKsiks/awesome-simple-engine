#ifndef ASENGINE_COMPONENT_MANAGER_H
#define ASENGINE_COMPONENT_MANAGER_H

#include <cstdint>
#include <type_traits>

#include "Component.h"
#include "engine/Singleton/Singleton.h"

namespace ASEngine
{
    // singleton that manages components
    class ComponentManager: public Singleton<ComponentManager>
    {
    public:
        // register component
        template <typename T>
        static inline void RegisterComponent(UniqueString componentName) { GetSingleton()->IRegisterComponent<T>(componentName); };

        // get signature of a composition of components
        template <typename T, typename... types>
        static uint32_t GetSignature();

    private:
        template <typename T>
        void IRegisterComponent(UniqueString componentName);

        // is valid signature <===> is prime
        bool IsValidSignature(uint32_t signature);

        // last component signature
        uint32_t m_LastComponentSignature = 1;

    };

    // implementations

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