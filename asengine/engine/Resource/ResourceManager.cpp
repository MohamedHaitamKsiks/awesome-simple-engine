
#include "ResourceManager.h"

namespace ASEngine {

    template <typename T>
    ResourceManager<T>* ResourceManager<T>::resourceManager = nullptr;

    template <typename T>
    ResourceManager<T>::~ResourceManager()
    {
        resourceIds.clear();
    };

    template <typename T>
    T* ResourceManager<T>::add(const UniqueString &resourceName)
    {
        ChunkID newResourceID = resources.alloc();
        resourceIds[resourceName.getId()] = newResourceID;

        resources.get(newResourceID)->id = newResourceID;

        return resources.get(newResourceID);
    }

    template <typename T>
    void ResourceManager<T>::remove(const UniqueString &resourceName)
    {
        ResourceID resourceId = resourceIds[resourceName.getId()];
        resources.free((ChunkID) resourceId);
        resourceIds.erase(resourceName.getId());
    }

    template <typename T>
    T* ResourceManager<T>::get(ResourceID resourceId)
    {
        return resources.get(resourceId);
    }

    template <typename T>
    ResourceID ResourceManager<T>::getResourceId(const UniqueString &resourceName)
    {
        return resourceIds[resourceName.getId()];
    }


} // ASEngine