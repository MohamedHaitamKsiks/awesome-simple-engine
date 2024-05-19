#ifndef ASENGINE_RESOURCE_H
#define ASENGINE_RESOURCE_H

#include "ResourceID.h"
#include "AbstractResource.h"
#include "IResourceClass.h"
#include "ResourceManager.h"

#include "Core/Memory/PoolAllocator.h"
#include "Core/String/UniqueString.h"
#include "Core/Serialization/Serializer.h"

#include "Class/Class.h"

namespace ASEngine
{
    // base class for resource
    template<typename T>
    class Resource: public AbstractResource
    {
    ASENGINE_DEFINE_CLASS(T);

    public:
        // make type polymorphic
        virtual ~Resource() {}

        // get resource class of the type
        static inline IResourceClass& GetResourceClass()
        {
            return ResourceManager::GetInstance().GetResouceClass(GetName());
        }
        
        void Deserialize(const Json &object) override
        {
            Serializer<T>::Deserialize(object, *(static_cast<T*>(this)));
        }
        
        Json Serialize() const override
        {
            return Serializer<T>::Serialize(*(static_cast<const T*>(this)));
        }
    };

} // namespace ASEngine


#endif