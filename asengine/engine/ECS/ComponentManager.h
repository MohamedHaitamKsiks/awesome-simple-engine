#ifndef ASENGINE_COMPONENT_MANAGER_H
#define ASENGINE_COMPONENT_MANAGER_H

#include <cstdint>
#include <type_traits>

#include "Component.h"
#include "../Singleton/Singleton.h"

namespace ASEngine
{
    // singleton that manages components
    class ComponentManager: public Singleton<ComponentManager>
    {
    public:
        // register component
        template<typename T>
        void registerComponent(UniqueString componentName);

        // get signature of a composition of components
        template<typename T, typename... types>
        uint32_t getSignature();
        
    private:
        // is valid signature <===> is prime
        bool isValidSignature(uint32_t signature);

        // last component signature
        uint32_t lastComponentSignature = 1;

    };

    // implementations

    // register component implementation
    template <typename T>
    void ComponentManager::registerComponent(UniqueString componentName)
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);

        // create signature
        int currentNumber = lastComponentSignature + 1;
        for (uint32_t i = lastComponentSignature + 1; i < UINT32_MAX; i++)
        {
            if (isValidSignature(i))
            {
                // register component
                T::signature = i;
                T::name = componentName;

                // update last component signature
                lastComponentSignature = i;
                return;
            }
        }
    };

    // get signature implementation
    template <typename T, typename... types>
    uint32_t ComponentManager::getSignature()
    {
        // check if component is of component type
        static_assert(std::is_base_of_v<Component<T>, T>);

        // compute signature
        uint32_t signature = T::signature;
        if constexpr (sizeof...(types) > 0)
        {
            signature *= getSignature<types...>();
        }

        return signature;
    };

} // namespace ASEngine


#endif