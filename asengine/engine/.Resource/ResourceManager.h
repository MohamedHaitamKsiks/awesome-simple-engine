#ifndef ASENGINE_RESOURCE_MANAGER_H
#define ASENGINE_RESOURCE_MANAGER_H

#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>
#include <cstdint>

#include "Resource.h"
#include "ResourceCollection.h"
#include "ECS/System.h"

namespace ASEngine
{
    // resource manager: 
    // Responsible for resource collections
    class ResourceManager: public ISystem
    {
    public:
        // register new resource type
        template<typename T>
        void RegisterResource(UniqueString resourceName)
        {
            static_assert(std::is_base_of_v<Resource<T>, T>);

            ASSERT(m_Resources.find(resourceName) == m_Resources.end(), "Resource Name Already Registered");

            // create collection
            std::unique_ptr<IResourceCollection> collection(new ResourceCollection<T>());

            // register resource
            Resource<T>::s_Name = resourceName;
            m_Resources[resourceName] = resourceInfo;
        }

        void Init();

        void Terminate();
        
        // create new resource
        ResourceID Create(UniqueString resourceName, UniqueString referenceName = UNIQUE_STRING_NULL);

        // delete resource
        void Delete(UniqueString resourceName, ResourceID resourceID);
    
        // resource id  
        ResourceID GetResourceID(UniqueString resourceName, UniqueString referenceName);

        // get resource 
        Resource& GetResource(UniqueString resourceName)

        template<typename T>
        inline ResourceID Create(UniqueString referenceName = UNIQUE_STRING_NULL)
        {
            return Create(Resource<T>::GetName(), referenceName);
        }

    private:
        std::unordered_map<UniqueString, std::unique_ptr<IResourceCollection>> m_ResourceCollections{};

    };


} // namespace ASEngine

#endif // ASENGINE_RESOURCE_MANAGER_H