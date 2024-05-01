#ifndef ASENGINE_RESOURCE_H
#define ASENGINE_RESOURCE_H

#include "Core/String/UniqueString.h"

namespace ASEngine
{
    using ResourceID = uint32_t;
    constexpr const ResourceID RESOURCE_ID_NULL = UINT32_MAX;

    // Resource Interface 
    class IResource 
    {
    public:
        // load resource from file
        virtual void Load(const std::string& path) = 0;
    };

    // base class for resource
    template<typename T>
    class Resource: public IResource
    {
    public:
        // get resource reference name
        // returns Null string if not named
        inline UniqueString GetReferenceName() const
        {
            return m_ReferenceName;
        }

        inline ResourceID GetResourceID() const
        {
            return m_ResourceID;
        }

        static UniqueString GetName()
        {
            return s_Name;
        }

    private:
        UniqueString m_ReferenceName = UNIQUE_STRING_NULL;
        ResourceID m_ResourceID;

        static UniqueString s_Name;

        friend class ResourceManager<T>;
    };

    template<typename T>
    UniqueString Resource<T>::s_Name = UNIQUE_STRING_NULL;

} // namespace ASEngine


#endif