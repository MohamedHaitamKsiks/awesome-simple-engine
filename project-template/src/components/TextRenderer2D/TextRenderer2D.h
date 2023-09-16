#ifndef COMPONENT_TEXTRENDERER2D_H
#define COMPONENT_TEXTRENDERER2D_H

#include<string>

#include "ASEngine.h"

using namespace ASEngine;

struct TextRenderer2D: public TComponent<TextRenderer2D>
{
	UniqueString FontName;
	ResourceID FontID = CHUNK_NULL;
	std::string Text;
	Color Modulate = Color::WHITE();

	void OnCreate();
};

#endif // COMPONENT_TEXTRENDERER2D_H