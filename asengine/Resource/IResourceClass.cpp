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
        UniqueString className = GetClassName();
        const std::string &name = className.GetString();

        // get imports
        if (!importObject.contains(name))
            return;

        auto &pathList = importObject[name];
        for (auto &path : pathList)
        {
            UniqueString resourceName{ std::string(path) };
            ResourceRef<Resource> resource = Load(resourceName);
            resource->SetPersistent(true); // because all resources imported from import.json are persistent
        }
    }


} // namespace ASEngine
