#ifndef ASENGINE_ABSTARCT_RESOURCE_H
#define ASENGINE_ABSTARCT_RESOURCE_H

#include "Class/Object.h"

#include "Core/String/UniqueString.h"
#include "Core/Serialization/Json.h"
#include "ResourceID.h"

namespace ASEngine
{
    // Abstract Resource 
    class Resource: public Object
    {
    public:
        virtual ~Resource() {};

        // load resource from file (return false if path was not found)
        // by default it deserialize the json object on load 
        // override if your resource is not serializable 
        virtual bool Load(const std::string& path);
        
        // save resource to file 
        void Save(const std::string& path);

        // get reference count
        inline uint32_t GetReferenceCount() const
        {
            return m_ReferenceCounter;
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
        virtual void Deserialize(const Json& object);
        
        // serialized resource
        virtual Json Serialize() const;

    private:
        ResourceID m_ResourceID = RESOURCE_ID_NULL;
        uint32_t m_ReferenceCounter = 0;
        bool m_IsPersistent = false;
        bool m_IsLoaded = false;
        UniqueString m_Path;

        inline void IncrementReferenceCounter()
        {
            m_ReferenceCounter++;
        }
        void DecrementReferenceCounter();
        void Destroy();
        
        template<typename T>
        friend class ResourceRef;

        template <typename T>
        friend class ResourceClass;
    };

} // namespace ASEngine

#endif // ASENGINE_ABSTARCT_RESOURCE_H