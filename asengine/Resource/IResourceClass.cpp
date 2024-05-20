#include "ResourceClass.h"
#include "Core/FileSystem/File.h"
#include "IResourceClass.h"

namespace ASEngine
{

    void IResourceClass::Init()
    {
        // load import file
        File importFile;
        ASENGINE_ASSERT(importFile.Open("import.json", FileOpenMode::READ), "Couldn't load import.json!");
        Json importObject = Json::parse(importFile.ReadText());
        importFile.Close();

        // get resource name
        const std::string &name = GetClassName().GetString();

        // get imports
        if (!importObject.contains(name))
            return;

        auto &pathList = importObject[name];
        for (auto &path : pathList)
        {
            UniqueString resourceName{ std::string(path) };
            ResourceRef<AbstractResource> resource = New(resourceName);
            
            // load resource
            if (!resource->Load(path))
            {
                Debug::Error("Can't find resource: ", path);
                continue;
            }
            
            resource->SetPersistent(true); // because all resources imported from import.json are persistent
        }
    }


} // namespace ASEngine
