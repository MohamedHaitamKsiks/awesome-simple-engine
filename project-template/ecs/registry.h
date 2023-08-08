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
    // sprite
    SpriteID spriteId = ResourceManager<Sprite>::GetResourceId(UniqueString("sprites/run.sprite.json"));
    auto& sprite = ResourceManager<Sprite>::Get(spriteId);
    
    // component registry ...
    ComponentManager::RegisterComponent<SpriteComponent>(UniqueString("Sprite"));
    ComponentManager::RegisterComponent<TransformComponent>(UniqueString("Transform"));

    // system registry ...
    SystemManager::RegisterSystem<SpriteRenderingSystem>();

    // create entities
    for (int i = 0; i < 20000; i++)
    {
        TransformComponent transformComponent;
        transformComponent.Position.x = Random::Range(-200.0f, 200.0f);
        transformComponent.Position.y = Random::Range(-200.0f, 200.0f);

        SpriteComponent spriteComponent;
        spriteComponent.MaterialID = sprite.GetDefaultMaterial();
        spriteComponent.Size = vec2{(float)sprite.GetWidth(), (float) sprite.GetHeight()};
        spriteComponent.Frames = sprite.GetFrames();

        Entity entity = World::Create(
            spriteComponent,
            transformComponent
        );
    }
    
};



#endif