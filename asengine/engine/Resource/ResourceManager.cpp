
#include "ResourceManager.h"

namespace ASEngine {

    template <typename T>
    ResourceManager<T>* ResourceManager<T>::s_Singleton = nullptr;

    template <typename T>
    ResourceManager<T>::ResourceManager(const std::string &resourceName)
    {
        static_assert(std::is_base_of_v<Resource, T>);
        LoadAll(resourceName);
    }

    template <typename T>
    void ResourceManager<T>::Init(const std::string &resourceName)
    {
        if (!s_Singleton)
            s_Singleton = new ResourceManager<T>(resourceName);
    }

    template <typename T>
    void ResourceManager<T>::Terminate()
    {
        if (s_Singleton)
            delete s_Singleton;
    }

    // default implementation
    template <typename T>
    void ResourceManager<T>::LoadAll(const std::string &resourceName)
    {
        //open import.json
        File importFile;
        importFile.Open("import.json", FileOpenMode::READ);

        // parse json
        auto importObject = Json::parse(importFile.ReadText());
        auto resourceList = importObject[resourceName];

        for (auto resource: resourceList)
        {
            ResourceID newResourceID = IAdd(UniqueString(std::string(resource)));
            auto& newResource = m_Resources.Get(newResourceID);

            if constexpr(std::is_same_v<T, Shader>)
            {
                newResource.Load(resource);
            }
            else 
            {
                File file;
                file.Open(std::string(resource), FileOpenMode::READ);
                Serializer<T>::Deserialize(Json::parse(file.ReadText()), newResource);
                file.Close();
            }

        }
        importFile.Close();
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