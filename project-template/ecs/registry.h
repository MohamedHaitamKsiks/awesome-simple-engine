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
    // load texture
    Image image;
    image.Load("images/spr_run.png");
    Texture texture = Texture::LoadFromImage(image);

    // register default shader
    ShaderID shaderId = ResourceManager<Shader>::Add();
    ResourceManager<Shader>::Get(shaderId)->Load("shaders/default.glsl");
    
    // register default material
    MaterialID materialId = ResourceManager<Material>::Add();
    ResourceManager<Material>::Get(shaderId)->Create(shaderId);
    ResourceManager<Material>::Get(shaderId)->SetShaderParam(UniqueString("u_Texture"), texture);

    // component registry ...
    ComponentManager::RegisterComponent<SpriteComponent>(UniqueString("Sprite"));
    ComponentManager::RegisterComponent<TransformComponent>(UniqueString("Transform"));

    // system registry ...
    SystemManager::RegisterSystem<SpriteRenderingSystem>();

    for (int i = 0; i < 1; i++)
    {
        TransformComponent transform;
        SpriteComponent sprite;
        sprite.MatID = materialId;
        sprite.SpriteTexture = texture;

        Entity entity = World::Create(
            sprite,
            transform
        );
    }
    
};



#endif