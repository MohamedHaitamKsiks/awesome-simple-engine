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
	//draw text
	Graphics::drawText("Hello World!\nHow are you doing?", vec2{16.0f, 320.0f}, "ft_pixel");
	//draw fps
	std::stringstream ss;
	ss << avgFps << " FPS";
	Graphics::drawText(ss.str(), vec2{16.0f, 16.0f}, "ft_pixel");
	//draw rectangles
	/*
		Graphics::drawRectangle(vec2{12.0f, 12.0f}, vec2{88.0f, 24.0f}, Color::white);
		Graphics::drawRectangle(vec2{14.0f, 14.0f}, vec2{84.0f, 20.0f}, Color::black);
		Graphics::drawRectangle(vec2{16.0f, 16.0f}, vec2{80.0f, 16.0f}, Color::green);
	 */
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
