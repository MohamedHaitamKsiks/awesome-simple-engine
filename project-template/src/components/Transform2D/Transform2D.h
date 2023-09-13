#ifndef COMPONENT_TRANSFORM2D_H
#define COMPONENT_TRANSFORM2D_H

#include "ASEngine.h"

using namespace ASEngine;

struct Transform2D: public TComponent<Transform2D>
{
	vec2 Position = vec2::ZERO();
	vec2 Scale = vec2::ONE();
	float Rotation = 0.0f;

	void OnCreate();
};

#endif // COMPONENT_TRANSFORM2D_H