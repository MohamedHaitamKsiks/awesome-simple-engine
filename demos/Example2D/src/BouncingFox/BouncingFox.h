#ifndef __ASENGINE_BOUNCING_FOX_H
#define __ASENGINE_BOUNCING_FOX_H

#include "ASEngine.h"
#include "Core/Math/Vector2.h"
using namespace ASEngine;

struct BouncingFox: public Component<BouncingFox>
{
    Vector2 Velocity = Vector2::ZERO();

    void OnCreate(EntityID entityID) override;
    void OnDestroy() override;
};

#endif // __ASENGINE_BOUNCING_FOX_H
