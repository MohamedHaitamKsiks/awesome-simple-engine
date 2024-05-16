#ifndef ASENGINE_RESOURCE_H
#define ASENGINE_RESOURCE_H

#include "ResourceID.h"
#include "AbstractResource.h"
#include "ResourceClass.h"

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
        void Deserialize(const Json &object) override
        {
            Serializer<T>::Deserialize(object, *(static_cast<T*>(this)));
        }
        
        Json Serialize() const override
        {
            return Serializer<T>::Serialize(*(static_cast<const T*>(this)));
        }

    private:
        void Destroy() override
        {
            IResourceClass& resourceClass = ResourceClass<T>::GetInstance();
            resourceClass.Destroy(*this);
        }
    };

} // namespace ASEngine


#endif