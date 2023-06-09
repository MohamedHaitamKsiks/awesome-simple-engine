//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_MYOBJECT_H
#define ANDROIDSIMPLEENGINE_MYOBJECT_H

#include <sstream>
#include "engine/asengine.h"

using namespace ASEngine;

class NewObject: public GameObject {

	float time = 0.0f;

	//functions for the different events for a game object
	void onCreate() {

	}

	void onUpdate(float delta) {
		time += delta;
	}

	void onDraw(Graphics& graphics) {
		graphics.drawSprite("spr_run", 8.0f * time, position);
	}
	
	void onInputEvent(InputEvent event) {
		
	}

};


#endif //ANDROIDSIMPLEENGINE_MYOBJECT_H
