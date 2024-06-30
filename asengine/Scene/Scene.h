#ifndef __ASENGINE_SCENE_H
#define __ASENGINE_SCENE_H

#include <vector>

#include "Resource/Resource.h"
#include "Resource/ResourceDefinition.h"
#include "Resource/ResourceRef.h"
#include "Resource/ResourceSerialization.h"

#include "ECS/EntityBuilder.h"

#include "API/API.h"

namespace ASEngine
{
    class ASENGINE_API Scene: public Resource
    {
    ASENGINE_DEFINE_RESOURCE(Scene);
    ASENGINE_SERIALIZE_RESOURCE(Scene);
    public:
        ~Scene() {}

        // create scene from a list of entity builders
        void Create(const std::vector<EntityBuilder>& builders);

        // instanciate scene
        void Instanciate();
        
    private:
        std::vector<EntityBuilder> m_Builders{};
        
        friend class Serializer;
        friend class SceneManager;
    }; 
} // namespace ASEngine

#endif // __ASENGINE_SCENE_H
