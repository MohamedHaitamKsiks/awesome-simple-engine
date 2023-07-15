#ifndef ASENGINE_ECS_REGISTRY_H
#define ASENGINE_ECS_REGISTRY_H

#include "components/SpriteComponent.h"
#include "components/TransformComponent.h"

#include "systems/SpriteRenderingSystem.h"
#include "engine/asengine.h"

using namespace ASEngine;

// register ecs
void ECSRegistry()
{
    
    // component registry ...
    ComponentManager::getSingleton()->registerComponent<SpriteComponent>(UniqueString("Sprite"));
    ComponentManager::getSingleton()->registerComponent<TransformComponent>(UniqueString("Transform"));

    // system registry ...
    SystemManager::getSingleton()->registerSystem<SpriteRenderingSystem>();
    
    // entity registry
    SpriteComponent sprite = SpriteComponent{
        ResourceManager<Sprite>::getSingleton()->getResourceId(UniqueString("spr_run"))
    };
    
    
    for (int i = 0; i < 100; i++)
    {
        TransformComponent transform = TransformComponent{
            vec2{
                Random::rand_rangef(0, 180),
                Random::rand_rangef(0, 320)
            },
            vec2{100.0f, 0.0f}.rotate(Random::rand_rangef(0.0f, 3.1415f))
        };

        Entity entity = World::getSingleton()->create(
            sprite,
            transform
        );

        World::getSingleton()->getComponent<TransformComponent>(entity)->owner = entity;
        
    }
    
};



#endif