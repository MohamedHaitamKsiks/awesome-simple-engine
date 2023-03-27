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
}

void MyObject::onDraw() {
	Graphics::drawSprite("spr_run",  8.0f * time, position, scale, rotation);
	Graphics::drawRectangle(vec2{12.0f, 12.0f}, vec2{88.0f, 24.0f}, Color::white);
	Graphics::drawRectangle(vec2{14.0f, 14.0f}, vec2{84.0f, 20.0f}, Color::black);
	Graphics::drawRectangle(vec2{16.0f, 16.0f}, vec2{80.0f, 16.0f}, Color::green);
}

void MyObject::onInputEvent(InputEvent event) {
	if (event.type == INPUT_EVENT_POINTER_DOWN || event.type == INPUT_EVENT_POINTER_MOVE) {
		direction = event.pointerPosition;
	}
}
