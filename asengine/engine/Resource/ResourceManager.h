#ifndef ASENGINE_RESOURCE_MANAGER_H
#define ASENGINE_RESOURCE_MANAGER_H

#include <unordered_map>
#include <string>
#include <cassert>

#include "Resource.h"
#include "engine/Singleton/Singleton.h"
#include "engine/FileSystem/File.h"
#include "engine/Memory/PoolAllocator.h"
#include "engine/String/UniqueString.h"
#include "engine/Log/Log.h"


namespace ASEngine {

    template <typename T>
    class ResourceManager
    {
    public:
        ResourceManager();

        // initiate resource manager
        static void Init();

        // get resource manager
        static inline ResourceManager<T>* GetSingleton()
        {
            return s_Singleton;
        };

        // terminate
        static void Terminate();

        //add new resource and give it a name
        static inline T *Add(const UniqueString &resourceName){
            return GetSingleton()->IAdd();
        };

        //remove resource by id
        static inline void Remove(const UniqueString &resourceName)
        {
            GetSingleton()->IRemove(resourceName);
        };

        //get resource by id
        static inline T *Get(ResourceID resourceId) 
        { 
            return GetSingleton()->m_Resources.Get(resourceId); 
        };

        //get resource id by name, make sure to cache it if you want to use it multiple time.
        static inline ResourceID GetResourceId(const UniqueString &resourceName)
        { 
            return GetSingleton()->m_ResourceIds[resourceName];
        };

    private:
        static ResourceManager<T>* s_Singleton;

        PoolAllocator<T> m_Resources{};
        std::unordered_map<UniqueString, ResourceID> m_ResourceIds = {};

        // add new resource and give it a name
        T *IAdd(const UniqueString &resourceName);
        // remove resource by id
        void IRemove(const UniqueString &resourceName);
    };

} // ASEngine

//include implementation
#include "ResourceManager.cpp"

#endif // ASENGINE_RESOURCE_MANAGER_H
