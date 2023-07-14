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
    auto archetype = ArchetypeManager::getSingleton()->getArchetype<SpriteComponent, TransformComponent>();
    Entity entity = World::getSingleton()->createEntity(archetype);
    
    // set sprite
    auto sprite = World::getSingleton()->getComponentOfEntity<SpriteComponent>(entity);
    sprite->spriteId = ResourceManager<Sprite>::getSingleton()->getResourceId(UniqueString("spr_run"));
    
    // set position
    auto transform = World::getSingleton()->getComponentOfEntity<TransformComponent>(entity);
    transform->position = Screen::getCenter();
};



#endif