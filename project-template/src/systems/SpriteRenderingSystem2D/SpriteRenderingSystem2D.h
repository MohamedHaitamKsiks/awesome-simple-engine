#ifndef SYSTEM_SPRITERENDERINGSYSTEM2D_H
#define SYSTEM_SPRITERENDERINGSYSTEM2D_H

#include "components/SpriteRenderer2D/SpriteRenderer2D.h"
#include "components/Transform2D/Transform2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class SpriteRenderingSystem2D: public System<SpriteRenderer2D, Transform2D>
{

	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_SPRITERENDERINGSYSTEM2D_H