#ifndef ASENGINE_RESOURCE_CLASS_H
#define ASENGINE_RESOURCE_CLASS_H

#include <cstdint>
#include <unordered_map>

#include "Core/Singleton/Singleton.h"
#include "Core/Error/Assertion.h"
#include "Core/String/UniqueString.h"
#include "Core/Memory/PoolAllocator.h"

#include "ECS/System.h"

#include "ResourceID.h"
#include "AbstractResource.h"
#include "ResourceRef.h"

#include "Class/Class.h"

namespace ASEngine
{
    class IResourceClass: public ISystem
    {
    public:
        // create named resource
        virtual ResourceRef<AbstractResource> New(UniqueString resourceName = UniqueString("")) = 0;
        
        // get resource 
        virtual ResourceRef<AbstractResource> GetResource(UniqueString referenceName) = 0;

        // get class name
        virtual UniqueString GetClassName() = 0;

        // get resource count
        virtual size_t GetResourcesCount() const = 0;

    protected:
        void Init() override;
        virtual void Terminate() = 0;
        
        virtual void Destroy(AbstractResource& resource) = 0;
    
        template<typename U>
        friend class Resource;
    };

    
    template <typename T>
    class ResourceClass: public IResourceClass
    {
    ASENGINE_DEFINE_SINGLETON(ResourceClass);
    
    public:
        // get class name
        UniqueString GetClassName() override
        {
            return Class<T>::GetName();
        }

        ResourceRef<AbstractResource> GetResource(UniqueString referenceName) override
        {
            ASENGINE_ASSERT(m_ResourceReferenceNames.find(referenceName) != m_ResourceReferenceNames.end(), "Reference Name Not Existing");
            
            ResourceID resourceID = m_ResourceReferenceNames[referenceName];
            AbstractResource& resource = m_Resources.Get(resourceID);
            return ResourceRef<AbstractResource>(&resource);
        }

        // add with name, if name exists return the created resource name
        ResourceRef<AbstractResource> New(UniqueString referenceName = UniqueString("")) override
        {
            // check if resource name already exists
            if (m_ResourceReferenceNames.find(referenceName) != m_ResourceReferenceNames.end())
                return GetResource(referenceName);

            // create resource
            ResourceID resourceID = m_Resources.Allocate();
            AbstractResource& resource = m_Resources.Get(resourceID);
            resource.m_ReferenceCounter = 1;
            resource.m_ResourceID = resourceID;
            resource.m_IsPersistent = false;
            
            // add reference name
            if (referenceName.GetLength() != 0)
            {
                resource.m_ReferenceName = referenceName;
                m_ResourceReferenceNames[referenceName] = resourceID;
            }

            ResourceRef<AbstractResource> resourceReference(&resource);
            return resourceReference;
        }

        size_t GetResourcesCount() const override
        {
            return m_Resources.GetSize();
        }

    private:
        template<typename U>
        friend class Resource;

        PoolAllocator<T> m_Resources{UINT16_MAX};
        std::unordered_map<UniqueString, ResourceID> m_ResourceReferenceNames{};

        // remove
        void Destroy(AbstractResource &resource)
        {
            UniqueString referenceName = resource.GetReferenceName();
            if (referenceName != UniqueString(""))
            {
                m_ResourceReferenceNames.erase(referenceName);
            }

            m_Resources.Free(resource.GetResourceID());
        }

        // clean up class
        void Terminate() override
        {
            m_Resources.Clear();
            m_ResourceReferenceNames.clear();
        }   
    };

} // namespace ASEngine

#endif // ASENGINE_RESOURCE_CLASS_H