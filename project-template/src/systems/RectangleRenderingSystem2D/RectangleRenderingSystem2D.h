#ifndef SYSTEM_RECTANGLERENDERINGSYSTEM2D_H
#define SYSTEM_RECTANGLERENDERINGSYSTEM2D_H

#include "ASEngine.h"

#include "components/Transform2D/Transform2D.h"
#include "components/RectangleRenderer2D/RectangleRenderer2D.h"

using namespace ASEngine;

class RectangleRenderingSystem2D : public System<RectangleRenderer2D, Transform2D>
{
	// constructor
	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_RECTANGLERENDERINGSYSTEM2D_H