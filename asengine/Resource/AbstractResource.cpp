#include "AbstractResource.h"
#include "ResourceClass.h"
#include "ResourceManager.h"

#include "Core/FileSystem/File.h"
#include "Core/Debug/Debug.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{
    // load resource
    bool AbstractResource::Load(const std::string &path)
    {
        File resourceFile;
        if (!resourceFile.Open(path, FileOpenMode::READ))
        {
            Debug::Error("Couldn't load ", path, "!");
            return false;
        }

        // deserialize element
        Json resourceObject = Json::parse(resourceFile.ReadText());
        Deserialize(resourceObject);

        resourceFile.Close();
        
        Debug::Log(Debug::Colorized(Debug::TextColor::GREEN_BG, path, ": Loaded"));

        return true;
    }

    void AbstractResource::Save(const std::string &path)
    {
    }
    
    void AbstractResource::Destroy()
    {
        UniqueString resourceName = GetClassName();
        IResourceClass& resourceClass = ResourceManager::GetInstance().GetResouceClass(resourceName);
        resourceClass.Destroy(*this);
    }
    
    void AbstractResource::DecrementReferenceCounter()
    {
        m_ReferenceCounter--;

        // destroy if no more reference to it exists
        if (m_ReferenceCounter == 0 && !m_IsPersistent)
        {
            Destroy();
        }
    }

} // namespace ASEngine
