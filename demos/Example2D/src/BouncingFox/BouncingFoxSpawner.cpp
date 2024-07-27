#include "2D/Transform2D/Transform2D.h"
#include "BouncingFoxSpawner.h"
#include "BouncingFox.h"
#include "Core/Math/Random.h"
#include "Core/Math/Vector2.h"
#include "ECS/EntityBuilder.h"
#include "ECS/EntityManager.h"

ASENGINE_SERIALIZE_STRUCT(BouncingFoxSpawner, Count);

void BouncingFoxSpawner::OnCreate(EntityID entityID)
{
    for (uint32_t i = 0; i < Count; i++)
    {
        // craete entity builder
        EntityBuilder boucingFoxBuilder;

        BouncingFox fox;
        fox.Velocity = Vector2::RIGHT().Rotate(Random::Range(0.0f, 2.0f * Math::PI)) * Random::Range(150.0f, 300.0f);

        Transform2D transform;
        transform.Position = Vector2(320.0f, 180.0f) / 2.0f;

        boucingFoxBuilder.AddComponents(transform, fox);

        // spawn foxes
        EntityManager::GetInstance().Create(boucingFoxBuilder);
    }
}

void BouncingFoxSpawner::OnDestroy() {}
