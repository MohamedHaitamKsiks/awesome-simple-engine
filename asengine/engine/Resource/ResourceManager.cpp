
#include "ResourceManager.h"

namespace ASEngine {

    template <typename T>
    ResourceManager<T>* ResourceManager<T>::s_Singleton = nullptr;

    template <typename T>
    ResourceManager<T>::ResourceManager()
    {
        static_assert(std::is_base_of_v<Resource, T>);
    }

    template <typename T>
    void ResourceManager<T>::Init()
    {
        if (!s_Singleton)
            s_Singleton = new ResourceManager<T>();
    }

    template <typename T>
    void ResourceManager<T>::Terminate()
    {
        if (s_Singleton)
            delete s_Singleton;
    }

    template <typename T>
    ResourceID ResourceManager<T>::IAdd(const UniqueString& resourceName)
    {
        ChunkID newResourceID = m_Resources.Alloc();
        m_ResourceIds[resourceName] = newResourceID;
        ((Resource&) m_Resources.Get(newResourceID)).ID = newResourceID;
        return newResourceID;
    }

    template <typename T>
    ResourceID ResourceManager<T>::IAdd()
    {
        ChunkID newResourceID = m_Resources.Alloc();
        ((Resource&)m_Resources.Get(newResourceID)).ID = newResourceID;
        return newResourceID;
    }

    template <typename T>
    void ResourceManager<T>::IRemove(ResourceID resourceId)
    {
        m_Resources.Free( resourceId);
    }

} // ASEngine