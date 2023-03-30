//
// Created by ksiks_wa3r on 3/27/23.
//

#include "MyObject.h"

void MyObject::onCreate() {
	ALOG("My Object Instance Created");
	position = Screen::getCenter();
	direction = position;
	scale = vec2::one() * 2.0f;
}

void MyObject::onUpdate(float delta) {
	position = position + (direction - position) * 10.0f *  delta;
	time += delta;
	if (delta != 0.0f)
		fps = 1.0f / delta;
	sumFps += fps;
	frameCounter++;
	if (frameCounter > 2000000) {
		sumFps = 0.0f;
		frameCounter = 0;
	}
	avgFps = round(sumFps / frameCounter);
}

void MyObject::onDraw() {
	//draw sprite
	Graphics::drawSprite("spr_run",  8.0f * time, position, scale, rotation);

}


void MyObject::onInputEvent(InputEvent event) {
	if (event.type == INPUT_EVENT_POINTER_DOWN) {
		direction = event.pointerPosition;
		pointerIndex = event.pointerIndex;
			
	}
	else if (event.type == INPUT_EVENT_POINTER_MOVE) {
		if (pointerIndex == event.pointerIndex)
			direction = event.pointerPosition;
	}
}
