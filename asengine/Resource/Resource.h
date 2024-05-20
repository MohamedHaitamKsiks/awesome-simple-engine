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

// serialize resource type
#define ASENGINE_SERIALIZE_RESOURCE(T) \
public: \
    void Deserialize(const Json &object) override; \
    Json Serialize() const override

// implemente resource 
#define ASENGINE_SERIALIZE_RESOURCE_IMP(T) \
void T::Deserialize(const Json &object) \
{ \
    Serializer<T>::Deserialize(object, *(static_cast<T *>(this))); \
} \
\
Json T::Serialize() const \
{ \
    return Serializer<T>::Serialize(*(static_cast<const T *>(this))); \
} 


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
    };

} // namespace ASEngine


#endif