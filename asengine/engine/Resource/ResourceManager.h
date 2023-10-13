#ifndef ASENGINE_RESOURCE_MANAGER_H
#define ASENGINE_RESOURCE_MANAGER_H

#include <unordered_map>
#include <string>
#include <cassert>

#include "Resource.h"
#include "Shader.h"
#include "Audio.h"

#include "Core/Singleton/Singleton.h"
#include "Core/FileSystem/File.h"
#include "Core/Memory/PoolAllocator.h"
#include "Core/String/UniqueString.h"
#include "Core/Serialization/Serializer.h"
#include "Core/Log/Log.h"

namespace ASEngine {

    template <typename T>
    class ResourceManager
    {
    public:
        ResourceManager(const std::string &name);

        // initiate resource manager
        static void Init(const std::string& name);

        // get resource manager
        static inline ResourceManager<T>* GetSingleton()
        {
            return s_Singleton;
        };

        // terminate
        static void Terminate();

        //add new resource and give it a name
        static inline ResourceID Add(const UniqueString &resourceName)
        {
            return GetSingleton()->IAdd(resourceName);
        };

        // add new unnamed resource
        static inline ResourceID Add()
        {
            return GetSingleton()->IAdd();
        };

        //remove resource by id
        static inline void Remove(ResourceID resourceId)
        {
            GetSingleton()->IRemove(resourceId);
        };

        //get resource by id
        static inline T& Get(ResourceID resourceId) 
        { 
            return GetSingleton()->m_Resources.Get(resourceId); 
        };

        //get resource id by name, make sure to cache it if you want to use it multiple time.
        static inline ResourceID GetResourceId(const UniqueString& resourceName)
        { 
            return GetSingleton()->m_ResourceIds[resourceName];
        };

    private:
        static ResourceManager<T>* s_Singleton;

        TPoolAllocator<T> m_Resources{UINT16_MAX};
        std::unordered_map<UniqueString, ResourceID> m_ResourceIds;
        std::string m_ResourceName;

        // add new resource and give it a name
        ResourceID IAdd(const UniqueString& resourceName);

        // add new resource
        ResourceID IAdd();

        // remove resource by id
        void IRemove(ResourceID resourceId);
    };

} // ASEngine

//include implementation
namespace ASEngine
{

    template <typename T>
    ResourceManager<T> *ResourceManager<T>::s_Singleton = nullptr;

    template <typename T>
    ResourceManager<T>::ResourceManager(const std::string& name)
    {
        static_assert(std::is_base_of_v<Resource, T>);
        m_ResourceName = name;

        // load all resources
        File importFile;
        if (!importFile.Open("import.json", FileOpenMode::READ))
        {
            Debug::Log("import.json IS MISSING!");
            return;
        }
        Json importObject = Json::parse(importFile.ReadText());
        importFile.Close();

        // get imports
        if (!importObject.contains(name)) return;

        auto& pathList = importObject[name];
        for (auto& path: pathList)
        {
            UniqueString resourceName = UniqueString(std::string(path));
            ResourceID resourceID = IAdd(resourceName);

            auto &resource = m_Resources.Get(resourceID);
            if (!resource.Load(path)) 
            {
                Debug::Log("Can't find ", path);
                IRemove(resourceID);
                return;
            }
            Debug::Log(path, " Loaded.");
        }

    }

    template <typename T>
    void ResourceManager<T>::Init(const std::string& name)
    {
        if (!s_Singleton)
        {
            s_Singleton = new ResourceManager<T>(name);
        }
    }

    template <typename T>
    void ResourceManager<T>::Terminate()
    {
        if (s_Singleton)
            delete s_Singleton;
    }

    template <typename T>
    ResourceID ResourceManager<T>::IAdd(const UniqueString &resourceName)
    {
        ChunkID newResourceID = m_Resources.Alloc();
        m_ResourceIds[resourceName] = newResourceID;
        ((Resource &)m_Resources.Get(newResourceID)).ID = newResourceID;
        return newResourceID;
    }

    template <typename T>
    ResourceID ResourceManager<T>::IAdd()
    {
        ChunkID newResourceID = m_Resources.Alloc();
        ((Resource &)m_Resources.Get(newResourceID)).ID = newResourceID;
        return newResourceID;
    }

    template <typename T>
    void ResourceManager<T>::IRemove(ResourceID resourceId)
    {
        m_Resources.Free(resourceId);
    }

} // ASEngine

#endif // ASENGINE_RESOURCE_MANAGER_H
