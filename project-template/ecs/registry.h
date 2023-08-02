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

    // sprite
    SpriteID spriteId = ResourceManager<Sprite>::Add();
    auto& sprite = ResourceManager<Sprite>::Get(spriteId);
    sprite.Load(texture, 6, vec2::ZERO());

    
    // register default shader ...
    ShaderID shaderId = ResourceManager<Shader>::Add();
    ResourceManager<Shader>::Get(shaderId).Load("shaders/default.glsl");

    
    // register default material ...
    MaterialID materialId = ResourceManager<Material>::Add();
    ResourceManager<Material>::Get(materialId).Create(shaderId);
    ResourceManager<Material>::Get(materialId).SetShaderParam(UniqueString("u_Texture"), texture);

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
        spriteComponent.MatID = materialId;
        spriteComponent.Size = vec2{(float)sprite.GetWidth(), (float) sprite.GetHeight()};
        spriteComponent.Frames = sprite.GetFrames();

        Entity entity = World::Create(
            spriteComponent,
            transformComponent
        );
    }
    
};



#endif