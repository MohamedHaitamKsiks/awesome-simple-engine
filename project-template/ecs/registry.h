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
    ComponentManager::RegisterComponent<SpriteComponent>(UniqueString("Sprite"));
    ComponentManager::RegisterComponent<TransformComponent>(UniqueString("Transform"));

    // system registry ...
    SystemManager::RegisterSystem<SpriteRenderingSystem>();

    for (int i = 0; i < 100; i++)
    {
        TransformComponent transform;
        SpriteComponent sprite;

        Entity entity = World::Create(
            sprite,
            transform
        );
    }
    
};



#endif