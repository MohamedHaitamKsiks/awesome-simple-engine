#ifndef __ASENGINE_RESOURCE_REF_H
#define __ASENGINE_RESOURCE_REF_H

#include "Resource.h"


namespace ASEngine
{
    // garbage collected reference to resource
    // AVOID CYCLIC REFERENCING
    template <typename T>
    class  ResourceRef
    {
    public:
        constexpr ResourceRef()
        {
            m_Instance = nullptr;
        }

        template<typename U>
        ResourceRef(const ResourceRef<U>& other)
        {
            static_assert(std::is_base_of_v<Resource, U>);
            static_assert(std::is_base_of_v<Resource, T>);

            m_Instance = dynamic_cast<T*>(other.m_Instance);
            if (m_Instance)
            {
                static_cast<Resource*>(m_Instance)->IncrementReferenceCounter();
            }
        }

        ResourceRef(const ResourceRef& other)
        {
            m_Instance = other.m_Instance;
            if (m_Instance)
            {
                static_cast<Resource *>(m_Instance)->IncrementReferenceCounter();
            }
        }

        inline ResourceRef& operator=(const ResourceRef& other)
        {
            // decrement current instance
            if (m_Instance)
            {
                static_cast<Resource *>(m_Instance)->DecrementReferenceCounter();
            }

            // copy new instance
            m_Instance = other.m_Instance;
            if (other.m_Instance)
            {
                static_cast<Resource *>(m_Instance)->IncrementReferenceCounter();
            }

            return *this;
        }

        ResourceRef(ResourceRef &&other) noexcept
        {
            m_Instance = other.m_Instance;
            if (other.m_Instance)
            {
                static_cast<Resource *>(m_Instance)->IncrementReferenceCounter();
            }
        }

        ResourceRef& operator=(ResourceRef&& other) noexcept
        {
            // decrement current instance
            if (m_Instance)
            {
                static_cast<Resource *>(m_Instance)->DecrementReferenceCounter();
            }

            // copy new instance
            m_Instance = other.m_Instance;
            if (other.m_Instance)
            {
                static_cast<Resource *>(m_Instance)->IncrementReferenceCounter();
            }

            return *this;
        }

        ~ResourceRef()
        {
            if (m_Instance)
            {
                static_cast<Resource*>(m_Instance)->DecrementReferenceCounter();
            }
        }

        T* operator->() const
        {
            return m_Instance;
        }

        // test equality of two reference (are they referencing to the same thing)
        inline constexpr bool operator==(const ResourceRef& ref) const
        {
            return m_Instance == ref.m_Instance;
        }

        inline constexpr bool operator!=(const ResourceRef &ref) const
        {
            return !(*this == ref);
        }

        // null constant
        static inline constexpr ResourceRef NONE()
        {
            return ResourceRef(nullptr);
        }

    private :
        T *m_Instance = nullptr;

        constexpr ResourceRef(T* instance): m_Instance(instance)
        {
            static_assert(std::is_base_of_v<Resource, T>);
        }


        template<typename U>
        friend class ResourceClass;

        template<typename U>
        friend class ResourceRef;
    };


} // namespace ASEngine


#endif // __ASENGINE_RESOURCE_REG_H
