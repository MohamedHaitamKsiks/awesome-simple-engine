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

    Log::out(ComponentManager::getSingleton()->getSignature<SpriteComponent, TransformComponent>());
    Log::out(ComponentManager::getSingleton()->getSignature<SpriteComponent>());

    // archetype registry ...

    // system registry ...
    SystemManager::getSingleton()->registerSystem<SpriteRenderingSystem>();
};



#endif