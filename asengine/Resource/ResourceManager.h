#ifndef __ASENGINE_RESOURCE_MANAGER_H
#define __ASENGINE_RESOURCE_MANAGER_H

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

#include "API/API.h"

// register abstract resource class
#define ASENGINE_REGISTER_ABSTRACT_RESOURCE_CLASS(base, imp) ResourceManager::GetInstance().RegisterAbstractResourceClass<base, imp>(UniqueString(#base))

// register resource class
#define ASENGINE_REGISTER_RESOURCE_CLASS(base) ResourceManager::GetInstance().RegisterResourceClass<base>(UniqueString(#base))

namespace ASEngine
{
    class Resource;

    // resource manager: 
    // Responsible for resource collections
    class ASENGINE_API ResourceManager
    {
    ASENGINE_DEFINE_SINGLETON(ResourceManager);

    public:
        // register abstract resource type with it's implementation
        template <typename Base, typename Derived>
        void RegisterAbstractResourceClass(UniqueString resourceName)
        {
            static_assert(std::is_base_of_v<Resource, Base>);
            static_assert(std::is_base_of_v<Base, Derived>);
        
            // register base class 
            ClassManager::GetInstance().RegisterClass<Base>(resourceName);  

            // add resource class of the derived 
            std::unique_ptr<IResourceClass> resourceClass = std::make_unique<ResourceClass<Derived>>(resourceName);
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
            ASENGINE_ASSERT(m_ResourceClasses.find(resourceName) != m_ResourceClasses.end(), "Resource class not registered");
            return *m_ResourceClasses[resourceName];
        }

    private:
        std::unordered_map<UniqueString, IResourceClass* > m_ResourceClasses{};
    };

} // namespace ASEngine

#endif // __ASENGINE_RESOURCE_MANAGER_H