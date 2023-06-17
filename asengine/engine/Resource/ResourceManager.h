#ifndef ASENGINE_RESOURCE_MANAGER_H
#define ASENGINE_RESOURCE_MANAGER_H

#include <unordered_map>
#include <string>
#include <cassert>

#include "Resource.h"
#include "../FileSystem/File.h"
#include "../Memory/PoolAllocator.h"
#include "../String/UniqueString.h"
#include "../Log/Log.h"


namespace ASEngine {

    template <typename T>
    class ResourceManager {
    public:
        static void init(size_t resourcesMaxNumber=INT16_MAX);
        static ResourceManager<T>* getSingleton();
        static void terminate();


        //add new resource and give it a name
        T* add(const UniqueString& resourceName);
        //remove resource by id
        void remove(const UniqueString &resourceName);
        //get resource by id
        T* get(ResourceID resourceId);
        //get resource id by name, make sure to cache it if you want to use it multiple time.
        ResourceID getResourceId(const UniqueString& resourceName);

        // constructor
        ResourceManager<T>() 
        {
            T t;
            assert(dynamic_cast<Resource*>(&t) != nullptr);
        }

        //destructor
        ~ResourceManager<T>();
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
