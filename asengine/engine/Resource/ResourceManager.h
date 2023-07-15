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
    class ResourceManager: public Singleton<ResourceManager<T>> {
    public:

        //add new resource and give it a name
        T* add(const UniqueString& resourceName);
        //remove resource by id
        void remove(const UniqueString &resourceName);
        //get resource by id
        T* get(ResourceID resourceId);
        //get resource id by name, make sure to cache it if you want to use it multiple time.
        ResourceID getResourceId(const UniqueString& resourceName);

        // constructor
        ResourceManager() 
        {
            //check if resource
            T t;
            assert(dynamic_cast<Resource*>(&t) != nullptr);

            resources.init(INT16_MAX);
        }

        //destructor
        ~ResourceManager();
    private:
        PoolAllocator<T> resources{};
        std::unordered_map<UniqueStringID, ResourceID> resourceIds = {};
        //singleton
        static ResourceManager<T>* resourceManager;
    };

} // ASEngine

//include implementation
#include "ResourceManager.cpp"

#endif // ASENGINE_RESOURCE_MANAGER_H
