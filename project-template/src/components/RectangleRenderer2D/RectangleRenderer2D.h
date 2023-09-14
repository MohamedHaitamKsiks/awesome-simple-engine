#ifndef COMPONENT_RECTANGLERENDERER2D_H
#define COMPONENT_RECTANGLERENDERER2D_H

#include "ASEngine.h"

using namespace ASEngine;

struct RectangleRenderer2D: public TComponent<RectangleRenderer2D>
{
	// rectangle size
	vec2 Size = vec2::ZERO();

	// rectangle color
	Color Modulate = Color::WHITE();

	// rectangle material
	static ResourceID DefaultMaterialID;
};

#endif // COMPONENT_RECTANGLERENDERER2D_H