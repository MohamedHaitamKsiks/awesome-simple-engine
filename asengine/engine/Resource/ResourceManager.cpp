
#include "ResourceManager.h"

namespace ASEngine {

    template <typename T>
    ResourceManager<T>* ResourceManager<T>::resourceManager = nullptr;

    template <typename T>
    void ResourceManager<T>::init(size_t resourceMaxNumber)
    {
        if (resourceManager)
            return;
        
        resourceManager = new ResourceManager<T>();
        resourceManager->resources.init(resourceMaxNumber);
    }

    template <typename T>
    ResourceManager<T>* ResourceManager<T>::getSingleton()
    {
        return resourceManager;
    }

    template <typename T>
    ResourceManager<T>::~ResourceManager<T>()
    {
        resourceIds.clear();
    };

    template <typename T>
    void ResourceManager<T>::terminate()
    {
        if (!resourceManager)
            return;
        delete resourceManager;
    }

    template <typename T>
    T* ResourceManager<T>::add(const ResourceName &resourceName)
    {
        ChunkId newResourceID = resources.alloc();
        resourceIds[resourceName] = newResourceID;

        resources.get(newResourceID)->id = newResourceID;

        return resources.get(newResourceID);
    }

    template <typename T>
    void ResourceManager<T>::remove(const ResourceName &resourceName)
    {
        ResourceID resourceId = resourceIds[resourceName];
        resources.free((ChunkId) resourceId);
        resourceIds.erase(resourceName);
    }

    template <typename T>
    T* ResourceManager<T>::get(ResourceID resourceId)
    {
        return resources.get(resourceId);
    }

    template <typename T>
    ResourceID ResourceManager<T>::getResourceId(const ResourceName &resourceName)
    {
        return resourceIds[resourceName];
    }


} // ASEngine