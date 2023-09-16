#ifndef SYSTEM_TEXTRENDERINGSYSTEM2D_H
#define SYSTEM_TEXTRENDERINGSYSTEM2D_H

#include "components/Transform2D/Transform2D.h"
#include "components/TextRenderer2D/TextRenderer2D.h"

#include "ASEngine.h"

using namespace ASEngine;

class TextRenderingSystem2D: public System<TextRenderer2D, Transform2D>
{

	void OnCreate();
	void OnUpdate(float delta);
	void OnRender2D();
	void OnInputEvent(const InputEvent& event);

};

#endif // SYSTEM_TEXTRENDERINGSYSTEM2D_H