#ifndef ASENGINE_RESOURCE_CLASS_H
#define ASENGINE_RESOURCE_CLASS_H

#include <cstdint>
#include <unordered_map>

#include "Core/Error/Assertion.h"
#include "Core/String/UniqueString.h"
#include "Core/Memory/PoolAllocator.h"

#include "ECS/System.h"

#include "ResourceID.h"
#include "Resource.h"
#include "ResourceRef.h"
#include "IResourceClass.h"

#include "Class/Class.h"

namespace ASEngine
{
    // implementation for each resource type
    template <typename T>
    class ResourceClass: public IResourceClass
    {
    public:
        // get class name
        UniqueString GetClassName() override
        {
            return Class<T>::GetName();
        }

        // load resource 
        ResourceRef<Resource> Load(UniqueString path) override
        {
            // load if not exists
            if (m_ResourcePaths.find(path) == m_ResourcePaths.end())
            {
                ResourceRef<Resource> resource = New();
                
                ASENGINE_ASSERT(resource->Load(path.GetString()), "Couldn't load resource");
                resource->m_Path = path;

                m_ResourcePaths[path] = resource->GetResourceID();

                return resource;
            }
            
            // get reference if exists
            ResourceID resourceID = m_ResourcePaths[path];
            Resource& resource = m_Resources.Get(resourceID);
            return ResourceRef<Resource>(&resource);
        }

        // create resource
        ResourceRef<Resource> New() override
        {
            // create resource
            ResourceID resourceID = m_Resources.Allocate();
            Resource& resource = m_Resources.Get(resourceID);
            resource.m_ReferenceCounter = 1;
            resource.m_ResourceID = resourceID;
            resource.m_IsPersistent = false;
            resource.m_Path = m_EmptyPath;

            ResourceRef<Resource> resourceReference(&resource);
            return resourceReference;
        }

        size_t GetResourcesCount() const override
        {
            return m_Resources.GetSize();
        }

    private:
        PoolAllocator<T> m_Resources{UINT16_MAX};
        // use paths as reference names
        std::unordered_map<UniqueString, ResourceID> m_ResourcePaths{};
        UniqueString m_EmptyPath{""};

        // remove
        void Destroy(Resource &resource)
        {
            if (resource.m_Path != m_EmptyPath)
            {
                m_ResourcePaths.erase(resource.m_Path);
            }

            m_Resources.Free(resource.GetResourceID());
        }

        // clean up class
        void Terminate() override
        {
            m_Resources.Clear();
            m_ResourcePaths.clear();
        }   
    };

} // namespace ASEngine

#endif // ASENGINE_RESOURCE_CLASS_H