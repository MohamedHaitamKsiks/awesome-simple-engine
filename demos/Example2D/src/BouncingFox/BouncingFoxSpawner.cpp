#include "BouncingFoxSpawner.h"
#include "BouncingFox.h"


ASENGINE_SERIALIZE_STRUCT(BouncingFoxSpawner, Count);

void BouncingFoxSpawner::Spawn(uint32_t count)
{
    EntityBuilder boucingFoxBuilder;
    boucingFoxBuilder.AddComponents(Transform2D{}, BouncingFox{});

    auto& fox = boucingFoxBuilder.GetComponent<BouncingFox>();
    auto& transform = boucingFoxBuilder.GetComponent<Transform2D>();

    for (uint32_t i = 0; i < count; i++)
    {
        // craete entity builder
        fox.Velocity = Vector2::RIGHT().Rotate(Random::Range(0.0f, 2.0f * Math::PI)) * Random::Range(150.0f, 300.0f);
        transform.Position = Vector2(320.0f, 180.0f) / 2.0f;

        // spawn foxes
        EntityManager::GetInstance().Create(boucingFoxBuilder);
    }
}

void BouncingFoxSpawner::OnCreate(EntityID entityID)
{
    Spawn(Count);
}

void BouncingFoxSpawner::OnDestroy() {}
