#ifndef ASENGINE_RESOURCE_DEFINITION_H
#define ASENGINE_RESOURCE_DEFINITION_H

#include "Resource.h"
#include "ResourceClass.h"
#include "ResourceManager.h"

#include "Class/Object.h"
#include "Class/Class.h"

// add to your resource class defintion
#define ASENGINE_DEFINE_RESOURCE(T) \
ASENGINE_DEFINE_CLASS(T) \
public: \
    static inline IResourceClass &GetResourceClass() \
    { \
        return ResourceManager::GetInstance().GetResouceClass(GetName()); \
    }

#endif // ASENGINE_RESOURCE_DEFINITION_H