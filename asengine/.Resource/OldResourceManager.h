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

    // interafce for resource manager
    /*class ResourceManager
    {
        
    };
    */

    template <typename T>
    class ResourceManager
    {
    public:
        ResourceManager(const std::string &name);

        //add new resource and give it a name
        ResourceID Add(const UniqueString &resourceName);

        // add new unnamed resource
        ResourceID Add();

        //remove resource by id
        void Remove(ResourceID resourceID);

        //get resource by id
        T& Get(ResourceID resourceID);

        //get resource id by name, make sure to cache it if you want to use it multiple time.
        ResourceID GetResourceID(const UniqueString& resourceName);

    private:
        TPoolAllocator<T> m_Resources{UINT16_MAX};
        std::unordered_map<UniqueString, ResourceID> m_ResourceIDs;
        std::string m_ResourceName;
    };

} // ASEngine

//include implementation
namespace ASEngine
{
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
