
#ifndef ANDROIDSIMPLEENGINE_MYOBJECT_H
#define ANDROIDSIMPLEENGINE_MYOBJECT_H

#include <sstream>
#include "engine/asengine.h"

using namespace ASEngine;

class NewObject: public GameObject {

	float time = 0.0f;
	ResourceID spriteId;
	ResourceID fontId;

	//functions for the different events for a game object
	void onCreate() {
		spriteId = ResourceManager<Sprite>::getSingleton()->getResourceId("spr_run");
		fontId = ResourceManager<Font>::getSingleton()->getResourceId("ft_default");
	}

	void onUpdate(float delta) {
		time += delta;
	}

	void onDraw(Graphics& graphics) {
		Sprite sprite = *ResourceManager<Sprite>::getSingleton()->get(spriteId);
		graphics.drawSprite(sprite, 8.0f * time, position);
		
		Font font = *ResourceManager<Font>::getSingleton()->get(fontId);
		graphics.drawText("Hello World!", vec2{64.0f, 64.0f}, font);
	}
	
	void onInputEvent(InputEvent event) {
		if (event.type == INPUT_EVENT_POINTER_DOWN) {
			position = event.pointerPosition;
		}
	}

};





#endif //ANDROIDSIMPLEENGINE_MYOBJECT_H
