#include "Resource.h"
#include "ResourceClass.h"
#include "ResourceManager.h"

#include "Core/Error/Assertion.h"
#include "Core/FileSystem/File.h"
#include "Core/Debug/Debug.h"
#include "Core/Serialization/Serializer.h"

namespace ASEngine
{
    // load resource
    bool Resource::Load(const std::string &path)
    {
        ASENGINE_ASSERT(!m_IsLoaded, "Resource can't be loaded more than once");

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
        
        m_IsLoaded = true;
        Debug::Log(Debug::Colorized(Debug::TextColor::GREEN_BG, path, ": Loaded"));

        return true;
    }

    void Resource::Save(const std::string &path)
    {
    }

    void Resource::Deserialize(const Json &object)
    {
        ASENGINE_ASSERT(false, GetClassName().GetString() + " Is NOT serializable");
    }

    Json Resource::Serialize() const
    {
        ASENGINE_ASSERT(false, GetClassName().GetString() + " Is NOT serializable");
        return Json();
    }

    void Resource::Destroy()
    {
        UniqueString resourceName = GetClassName();
        IResourceClass& resourceClass = ResourceManager::GetInstance().GetResouceClass(resourceName);
        resourceClass.Destroy(*this);
    }
    
    void Resource::DecrementReferenceCounter()
    {
        m_ReferenceCounter--;

        // destroy if no more reference to it exists
        if (m_ReferenceCounter == 0 && !m_IsPersistent)
        {
            Destroy();
        }
    }

} // namespace ASEngine
