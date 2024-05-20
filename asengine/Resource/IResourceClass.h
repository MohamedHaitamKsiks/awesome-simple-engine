#ifndef ASENGINE_IRESOURCE_CLASS_H
#define ASENGINE_IRESOURCE_CLASS_H

#include <cstdint>
#include <unordered_map>

#include "Core/String/UniqueString.h"

#include "ECS/System.h"

#include "AbstractResource.h"
#include "ResourceRef.h"

namespace ASEngine
{
    class IResourceClass: public ISystem
    {
    public:
        // create named resource
        virtual ResourceRef<AbstractResource> New(UniqueString referenceName = UniqueString("")) = 0;

        // lazy get resource (load if not exists) 
        virtual ResourceRef<AbstractResource> GetResource(UniqueString referenceName) = 0;

        // get class name
        virtual UniqueString GetClassName() = 0;

        // get resource count
        virtual size_t GetResourcesCount() const = 0;

    protected:
        void Init() override;
        virtual void Terminate() = 0;
    
        virtual void Destroy(AbstractResource& resource) = 0;

        friend class AbstractResource;
    };


} // namespace ASEngine

#endif // ASENGINE_IRESOURCE_CLASS_H