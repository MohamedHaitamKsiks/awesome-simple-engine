#ifndef ASENGINE_ECS_REGISTRY_H
#define ASENGINE_ECS_REGISTRY_H

// include components
#include "components/SpriteComponent.h"
#include "components/TransformComponent.h"

// include systems
#include "systems/SpriteRenderingSystem.h"
#include "systems/SpriteAnimationSystem.h"

// include asengine
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
    SystemManager::RegisterSystem<SpriteAnimationSystem>();
};

#endif