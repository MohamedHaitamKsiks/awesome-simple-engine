#ifndef ASENGINE_RESOURCE_MANAGER_H
#define ASENGINE_RESOURCE_MANAGER_H

#include <unordered_map>
#include <string>

#include "../FileSystem/File.h"
#include "../Memory/PoolAllocator.h"
#include "../Log/Log.h"

namespace ASEngine {

    //32 bits integer used to reference resources
    typedef ChunkId ResourceID;
    //resource name you can use it to get the resource reference
    typedef std::string ResourceName;

    template <typename T>
    class ResourceManager {
    public:
        static void init(size_t resourcesMaxNumber=INT16_MAX);
        static ResourceManager<T>* getSingleton();
        static void terminate();

        //add new resource and give it a name
        ResourceID add(const ResourceName& resourceName, const T& resource);
        //remove resource by id
        void remove(const ResourceName &resourceName);
        //get resource by id
        T& get(ResourceID resourceId);
        //get resource id by name, make sure to cache it if you want to use it multiple time.
        ResourceId getResourceId(const ResourceName& resourceName);

    private:
        PoolAllocator<T> resources{}
        std::unordered_map<ResourceName, ResourceID> resourceIds = {};
        //singleton
        static ResourceManager<T>* resourceManager;
    };

} // ASEngine

#endif // ASENGINE_RESOURCE_MANAGER_H
