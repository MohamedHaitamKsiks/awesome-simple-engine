#ifndef ASENGINE_ECS_REGISTRY_H
#define ASENGINE_ECS_REGISTRY_H

#include "ASEngine.h"
using namespace ASEngine;

#include "components/SpriteRenderer2D/SpriteRenderer2D.h"
#include "components/RectangleRenderer2D/RectangleRenderer2D.h"
#include "components/AudioPlayer2D/AudioPlayer2D.h"
#include "components/Transform2D/Transform2D.h"
#include "systems/SpriteRenderingSystem2D/SpriteRenderingSystem2D.h"
#include "systems/RectangleRenderingSystem2D/RectangleRenderingSystem2D.h"

// register ecs
void ECSRegistry();

#endif