#ifndef __ASENGINE_RESOURCE_CLASS_H
#define __ASENGINE_RESOURCE_CLASS_H

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

#include "API/API.h"

namespace ASEngine
{
    // implementation for each resource type
    template <typename T>
    class ASENGINE_API ResourceClass : public IResourceClass
    {
    public:
        ResourceClass(UniqueString className): m_ClassName(className)
        {
        }

        ~ResourceClass()
        {
        }

        // get class name
        UniqueString GetClassName() override
        {
            return m_ClassName;
        }

        // load resource 
        ResourceRef<Resource> Load(UniqueString path) override
        {
            // load if not exists
            if (m_ResourcePaths.find(path) == m_ResourcePaths.end())
            {
                ResourceRef<Resource> resource = New();
                
                if (!resource->Load(path.GetString()))
                {
                    Debug::Error("Couldn't load", path.GetString());
                    return ResourceRef<Resource>(nullptr);
                }
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
        PoolAllocator<T> m_Resources{};
        // use paths as reference names
        std::unordered_map<UniqueString, ResourceID> m_ResourcePaths{};
        UniqueString m_EmptyPath{""};
        UniqueString m_ClassName;

        // remove
        void Destroy(Resource &resource)
        {
            if (resource.m_Path != m_EmptyPath && m_ResourcePaths.find(resource.m_Path) != m_ResourcePaths.end())
            {
                m_ResourcePaths.erase(resource.m_Path);
            }

            // delete already deleted
            if (!m_Resources.IsFree(resource.GetResourceID()))
                m_Resources.Free(resource.GetResourceID());
        }

        // clean up class
        void Init() override
        {
        }

        void Terminate() override
        {
            m_ResourcePaths.clear();
            m_Resources.Clear();
        }   
    };

} // namespace ASEngine

#endif // __ASENGINE_RESOURCE_CLASS_H