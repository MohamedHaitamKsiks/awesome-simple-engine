#include "AbstractResource.h"
#include "ResourceClass.h"

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
        resourceFile.Close();
        
        Debug::Log(Debug::Colorized(Debug::TextColor::GREEN_BG, path, ": Loaded"));

        return true;
    }

    void AbstractResource::Save(const std::string &path)
    {
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
