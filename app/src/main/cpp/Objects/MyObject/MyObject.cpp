//
// Created by ksiks_wa3r on 3/27/23.
//

#include "MyObject.h"

void MyObject::onCreate() {
	position = vec2{(float(rand()) / float(RAND_MAX)), float(rand()) / float(RAND_MAX)} * Screen::getSize();
	float angle = 2.0f * 3.14f * float(rand()) / float(RAND_MAX);
	velocity = vec2::one().rotate(angle) * 200.0f;
	mask.size = vec2::one() * 32.0f;
}

void MyObject::onUpdate(float delta) {
	//collision
	if (position.x < 0.0f) {
		velocity.x *= -1.0f;
		position.x = 0.0f;
	}
	else if (position.x > Screen::getSize().x) {
		velocity.x *= -1.0f;
		position.x = Screen::getSize().x;
	}

	if (position.y < 0.0f) {
		velocity.y *= -1.0f;
		position.y = 0.0f;
	}
	else if (position.y > Screen::getSize().y) {
		velocity.y *= -1.0f;
		position.y = Screen::getSize().y;
	}
	//scale up
	scale = (scale * 15.0f + vec2::one() * 2.0f) / 16.0f;

	//if collide with something
	if (MyObject* object = (MyObject*)collideWithObject("MyObject", vec2{velocity.x, 0.0f} * delta)) {
		velocity.x *= -1.0f;
		//object->velocity.x *= -1.0f;
	}

	if (MyObject* object = (MyObject*)collideWithObject("MyObject", vec2{0.0f, velocity.y} * delta)) {
		velocity.y *= -1.0f;
		object->velocity.y *= -1.0f;
	}

	//move
	position = position + velocity * delta;
	time += delta;

}

void MyObject::onDraw() {
	//draw sprite
	Graphics::drawSprite("spr_run",  8.0f * time, position + vec2{0.0f, 2.0f}, Color::black);
	Graphics::drawSprite("spr_run",  8.0f * time, position);

	//draw mask
	Graphics::drawRectangle(mask.position, mask.size, Color{1.0f, 0.0f, 0.0f, 0.5});

}


void MyObject::onInputEvent(InputEvent event) {
	if (event.type == INPUT_EVENT_POINTER_DOWN) {
		velocity = (position - event.pointerPosition).normalized() * 200.0f;
	}
}
