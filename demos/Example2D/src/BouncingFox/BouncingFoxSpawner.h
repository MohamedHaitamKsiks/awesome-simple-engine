#ifndef __ASENGINE_BOUNCING_FOX_SPAWNER_H
#define __ASENGINE_BOUNCING_FOX_SPAWNER_H

#include "ASEngine.h"
#include "Core/Math/Vector2.h"
using namespace ASEngine;

struct BouncingFoxSpawner: public Component<BouncingFoxSpawner>
{
    uint32_t Count = 0;
    void Spawn(uint32_t count);

    void OnCreate(EntityID entityID) override;
    void OnDestroy() override;
};

#endif // __ASENGINE_BOUNCING_FOX_SPAWNER_H
