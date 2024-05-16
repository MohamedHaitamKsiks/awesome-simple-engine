#ifndef ASENGINE_RESOURCE_MANAGER_H
#define ASENGINE_RESOURCE_MANAGER_H

#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>
#include <cstdint>

#include "ResourceClass.h"
#include "Resource.h"

#include "ECS/System.h"
#include "ECS/SystemManager.h"

#include "Core/Singleton/Singleton.h"
#include "Core/Error/Assertion.h"

#include "Class/ClassManager.h"

namespace ASEngine
{
    // resource manager: 
    // Responsible for resource collections
    class ResourceManager
    {
    ASENGINE_DEFINE_SINGLETON(ResourceManager);

    public:
        // register new resource type
        template<typename T>
        void RegisterResourceClass(UniqueString resourceName)
        {
            static_assert(std::is_base_of_v<Resource<T>, T>);

            ASENGINE_ASSERT(m_ResourceClasses.find(resourceName) == m_ResourceClasses.end(), "Resource Name Already Registered");

            // register class
            ClassManager::GetInstance().RegisterClass<T>(resourceName);

            // add resource class system
            SystemManager::GetInstance().RegisterSystem<ResourceClass<T>>();

            // add resource class name
            IResourceClass& resourceClass = ResourceClass<T>::GetInstance();
            m_ResourceClasses[resourceName] = &resourceClass;
        }

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