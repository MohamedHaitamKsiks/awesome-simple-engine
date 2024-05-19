#ifndef ASENGINE_RESOURCE_REF_H
#define ASENGINE_RESOURCE_REF_H

#include "AbstractResource.h"

namespace ASEngine
{
    // garbage collected reference to resource
    // AVOID CYCLIC REFERENCING
    template <typename T>
    class ResourceRef
    {
    public:
        ResourceRef()
        {
            m_Instance = nullptr;
        }

        template<typename U>
        ResourceRef(const ResourceRef<U>& other)
        {
            static_assert(std::is_base_of_v<AbstractResource, U>);
            static_assert(std::is_base_of_v<AbstractResource, T>);

            m_Instance = dynamic_cast<T*>(other.m_Instance);
            if (m_Instance)
            {
                static_cast<AbstractResource*>(m_Instance)->IncrementReferenceCounter();
            }
        }

        ResourceRef(const ResourceRef& other)
        {
            m_Instance = other.m_Instance;
            if (m_Instance)
            {
                static_cast<AbstractResource *>(m_Instance)->IncrementReferenceCounter();
            }
        }

        inline ResourceRef& operator=(const ResourceRef& other)
        {
            // decrement current instance
            if (m_Instance)
            {
                static_cast<AbstractResource *>(m_Instance)->DecrementReferenceCounter();
            }

            // copy new instance
            m_Instance = other.m_Instance;
            if (other.m_Instance)
            {
                static_cast<AbstractResource *>(m_Instance)->IncrementReferenceCounter();
            }
            
            return *this;
        }

        ResourceRef(ResourceRef &&other) noexcept
        {
            m_Instance = other.m_Instance;
            other.m_Instance = nullptr;
        }

        ResourceRef& operator=(ResourceRef&& other) noexcept
        {
            m_Instance = other.m_Instance;
            other.m_Instance = nullptr;
            return *this;
        }

        ~ResourceRef()
        {
            if (m_Instance)
            {
                static_cast<AbstractResource*>(m_Instance)->DecrementReferenceCounter();
            }
        }

        T* operator->()
        {
            return m_Instance;
        }

        const T* operator->() const
        {
            return m_Instance;
        }
        
    private:
        T* m_Instance = nullptr;
        
        ResourceRef(T* instance): m_Instance(instance)
        {
            static_assert(std::is_base_of_v<AbstractResource, T>);
        }


        template<typename U>
        friend class ResourceClass;

        template<typename U>
        friend class ResourceRef;
    };

    
} // namespace ASEngine


#endif // ASENGINE_RESOURCE_REG_H