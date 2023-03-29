//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_MYOBJECT_H
#define ANDROIDSIMPLEENGINE_MYOBJECT_H

#include <sstream>
#include "../../engine/asengine.h"

using namespace ASEngine;

class MyObject: public GameObject {

	//direction
	vec2 direction = vec2::zero();
	//time
	float time = 0.0f;
	//pointer index
	int pointerIndex;
	//fps
	float fps = 0.0f;
	float avgFps = 0.0f;
	float sumFps = 0.0f;
	int frameCounter = 0;

	//functions for the different events for a game object (similar to gamemaker's events)
	void onCreate();
	void onUpdate(float delta);
	void onDraw();
	void onInputEvent(InputEvent event);
};


#endif //ANDROIDSIMPLEENGINE_MYOBJECT_H
