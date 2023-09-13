#ifndef COMPONENT_SPRITERENDERER2D_H
#define COMPONENT_SPRITERENDERER2D_H

#include "ASEngine.h"

using namespace ASEngine;

struct SpriteRenderer2D: public TComponent<SpriteRenderer2D>
{
	// sprite name
	UniqueString SpriteName;
	// sprite id
	ResourceID SpriteID;
	// sprite material
	ResourceID MaterialID;
	// frame rate
	float FrameRate = 0.0f;
	// current frame
	float Frame = 0.0f;
	// number of frames in this sprite
	uint32_t Frames = 0;
	// size
	vec2 Size = vec2::ZERO();
	// offset
	vec2 Offset = vec2::ZERO();
	// is centered
	bool Centered = false;
	// color
	Color Modulate = Color::WHITE();

	void OnCreate();
};

#endif // COMPONENT_SPRITERENDERER2D_H