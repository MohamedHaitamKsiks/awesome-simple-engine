#ifndef __ASENGINE_IRESOURCE_CLASS_H
#define __ASENGINE_IRESOURCE_CLASS_H

#include <cstdint>
#include <unordered_map>

#include "Core/String/UniqueString.h"

#include "ECS/System.h"

#include "Resource.h"
#include "ResourceRef.h"

namespace ASEngine
{
    class IResourceClass: public ISystem
    {
    public:
        // create named resource
        virtual ResourceRef<Resource> New() = 0;

        // lazy get resource (load if not exists) 
        virtual ResourceRef<Resource> Load(UniqueString path) = 0;

        // get class name
        virtual UniqueString GetClassName() = 0;

        // get resource count
        virtual size_t GetResourcesCount() const = 0;

    protected:
        void Init() override;
        virtual void Terminate() = 0;
    
        virtual void Destroy(Resource& resource) = 0;

        friend class Resource;
    };


} // namespace ASEngine

#endif // __ASENGINE_IRESOURCE_CLASS_H