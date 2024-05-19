#ifndef ASENGINE_ABSTARCT_RESOURCE_H
#define ASENGINE_ABSTARCT_RESOURCE_H

#include "Class/Object.h"

#include "Core/String/UniqueString.h"
#include "Core/Serialization/Json.h"
#include "ResourceID.h"

namespace ASEngine
{

    // Abstract Resource 
    class AbstractResource: public Object
    {
    public:
        // load resource from file (return false if path was not found)
        bool Load(const std::string& path);
        
        // save resource to file 
        void Save(const std::string& path);

        // get reference count
        inline uint32_t GetReferenceCount() const
        {
            return m_ReferenceCounter;
        }

        // get reference name
        inline UniqueString GetReferenceName() const
        {
            return m_ReferenceName;
        }

        // get resource id
        inline ResourceID GetResourceID() const
        {
            return m_ResourceID;
        }

        // set persistent (means that the resource is not deleted after there are no more reference to it)
        inline void SetPersistent(bool persistent)
        {
            m_IsPersistent = persistent;
        }

        // is resource persistent
        inline bool IsPersistent() const
        {
            return m_IsPersistent;
        }

        // deserialize resource
        virtual void Deserialize(const Json& object) = 0;
        
        // serialized resource
        virtual Json Serialize() const = 0;

    protected:
        void Destroy();

    private:
        ResourceID m_ResourceID = RESOURCE_ID_NULL;
        uint32_t m_ReferenceCounter = 0;
        UniqueString m_ReferenceName{""};
        bool m_IsPersistent = false;

        inline void IncrementReferenceCounter()
        {
            m_ReferenceCounter++;
        }
        void DecrementReferenceCounter();
        
        template<typename T>
        friend class ResourceRef;

        template <typename T>
        friend class ResourceClass;
    };

} // namespace ASEngine

#endif // ASENGINE_ABSTARCT_RESOURCE_H