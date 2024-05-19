#ifndef ASENGINE_RESOURCE_MANAGER_H
#define ASENGINE_RESOURCE_MANAGER_H

#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>
#include <cstdint>

#include "ResourceClass.h"

#include "ECS/System.h"
#include "ECS/SystemManager.h"

#include "Core/Singleton/Singleton.h"
#include "Core/Error/Assertion.h"

#include "Class/ClassManager.h"

namespace ASEngine
{
    template<typename T>
    class Resource;

    // resource manager: 
    // Responsible for resource collections
    class ResourceManager
    {
    ASENGINE_DEFINE_SINGLETON(ResourceManager);

    public:
        // register abstract resource type with it's implementation
        template <typename Base, typename Derived>
        void RegisterAbstractResourceClass(UniqueString resourceName)
        {
            static_assert(std::is_base_of_v<Resource<Base>, Base>);
            static_assert(std::is_base_of_v<Base, Derived>);
        
            // register base class 
            ClassManager::GetInstance().RegisterClass<Base>(resourceName);

            // add resource class of the derived 
            std::unique_ptr<IResourceClass> resourceClass = std::make_unique<ResourceClass<Derived>>();
            RegisterResourceClass(resourceName, std::move(resourceClass));
        }

        // register new resource type
        template <typename T>
        inline void RegisterResourceClass(UniqueString resourceName)
        {
            RegisterAbstractResourceClass<T, T>(resourceName);
        }

        // register resource class
        void RegisterResourceClass(UniqueString resourceName, std::unique_ptr<IResourceClass> resourceClass);

        // get resource class by name
        inline IResourceClass& GetResouceClass(UniqueString resourceName)
        {
            ASENGINE_ASSERT(m_ResourceClasses.find(resourceName) != m_ResourceClasses.end(), "Resource Class IS NOT Registered");
            return *m_ResourceClasses[resourceName];
        }

    private:
        std::unordered_map<UniqueString, IResourceClass* > m_ResourceClasses{};
    };

} // namespace ASEngine

#endif // ASENGINE_RESOURCE_MANAGER_H