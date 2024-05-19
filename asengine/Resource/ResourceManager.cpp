#include "ResourceManager.h"

namespace ASEngine
{

    void ResourceManager::RegisterResourceClass(UniqueString resourceName, std::unique_ptr<IResourceClass> resourceClass)
    {
        // add resource class name
        ASENGINE_ASSERT(m_ResourceClasses.find(resourceName) == m_ResourceClasses.end(), "Resource Name Already Registered");
        m_ResourceClasses[resourceName] = resourceClass.get();

        // add resource class system
        SystemManager::GetInstance().RegisterSystem(std::move(resourceClass));
    }

} // namespace ASEngine
