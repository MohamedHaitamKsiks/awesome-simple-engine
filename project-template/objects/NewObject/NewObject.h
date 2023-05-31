//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_MYOBJECT_H
#define ANDROIDSIMPLEENGINE_MYOBJECT_H

#include <sstream>
#include "asengine.h"

using namespace ASEngine;

class NewObject: public GameObject {

	//functions for the different events for a game object
	void onCreate() {

	}

	void onUpdate(float delta) {

	}

	void onDraw(Graphics& graphics) {
		graphics.drawSprite("spr_run", 0, position);
	}
	
	void onInputEvent(InputEvent event) {
		
	}

};


#endif //ANDROIDSIMPLEENGINE_MYOBJECT_H
