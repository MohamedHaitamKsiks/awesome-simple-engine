#ifndef ASENGINE_RESOURCE_MANAGER1_H
#define ASENGINE_RESOURCE_MANAGER_H

#include <cstdint>
#include <unordered_map>

#include "Core/Singleton/Singleton.h"
#include "Core/Error/Assert.h"
#include "Core/String/UniqueString.h"
#include "Core/Memory/PoolAllocator.h"
#include "Core/FileSystem/File.h"

#include "ECS/System.h"
#include "Resource.h"

namespace ASEngine
{
    template <typename T>
    class ResourceManager: public Singleton<ResourceManager<T>>, public ISystem
    {
    public:
        void Init()
        {
            static_assert(std::is_base_of_v<Resource<T>, T>);

            // load import file
            File importFile;
            ASSERT(importFile.Open("import.json", FileOpenMode::READ), "Couldn't load import.json!");
            Json importObject = Json::parse(importFile.ReadText());
            importFile.Close();

            // get resource name
            const std::string& name = Resource<T>::GetName().GetString();

            // get imports
            if (!importObject.contains(name))
                return;

            auto &pathList = importObject[name];
            for (auto &path : pathList)
            {
                UniqueString resourceName(std::string(path));
                ResourceID resourceID = Create(resourceName);

                auto &resource = Get(resourceID);
                if (!resource.Load(path))
                {
                    Debug::Error("Can't find ", path);
                    IRemove(resourceID);
                    continue;
                }
            }
        }

        void Terminate()
        {
            m_ResourceReferenceNames.clear();
            m_Resources.Clear();
        }

        ResourceID GetResourceID(UniqueString referenceName)
        {
            ASSERT(m_ResourceReferenceNames.find(referenceName) != m_ResourceReferenceNames.end(), "Reference Name Not Existing");
            return m_ResourceReferenceNames[referenceName];
        }

        // get resource
        inline T &Get(ResourceID resourceID)
        {
            return m_Resources.Get(resourceID);
        }

        // create resource
        ResourceID Create()
        {
            ResourceID createdResourceID = m_Resources.Allocate();
            Get(createdResourceID).m_ResourceID = createdResourceID;
            return createdResourceID;
        }

        // add with name
        ResourceID Create(UniqueString referenceName)
        {
            ASSERT(m_ResourceReferenceNames.find(referenceName) == m_ResourceReferenceNames.end(), "Reference Name Already Exists!!");
            
            ResourceID createdResourceID = Create();
            
            m_ResourceReferenceNames[referenceName] = createdResourceID;
            Get(createdResourceID).m_ReferenceName = referenceName;
            
            return createdResourceID;
        }

        // remove
        void Destroy(ResourceID resourceID)
        {
            UniqueString referenceName = Get(resourceID).GetReferenceName();
            if (referenceName != UNIQUE_STRING_NULL)
            {
                m_ResourceReferenceNames.erase(referenceName);
            }

            m_Resources.Free(resourceID);
        }

    private:
        PoolAllocator<T> m_Resources{UINT16_MAX};
        std::unordered_map<UniqueString, ResourceID> m_ResourceReferenceNames{};
    };

} // namespace ASEngine

#endif // ASENGINE_RESOURCE_MANAGER_H