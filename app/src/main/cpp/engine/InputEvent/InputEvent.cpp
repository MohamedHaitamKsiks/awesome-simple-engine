//
// Created by ksiks_wa3r on 3/27/23.
//

#include "InputEvent.h"

namespace ASEngine {
	void InputEvent::init(android_app *_app) {
		app = _app;
	}

	//pool event
	InputEvent InputEvent::poolEvent(int eventIndex) {
		//create event
		InputEvent event;

		//get event from game activity
		GameActivityMotionEvent motionEvent = app->motionEvents[eventIndex];

		int action = motionEvent.action;
		int actionMasked = action & AMOTION_EVENT_ACTION_MASK;
		int ptrIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

		if (actionMasked == AMOTION_EVENT_ACTION_DOWN || actionMasked == AMOTION_EVENT_ACTION_POINTER_DOWN) {
			event.type = INPUT_EVENT_POINTER_DOWN;
		} else if (actionMasked == AMOTION_EVENT_ACTION_UP || actionMasked == AMOTION_EVENT_ACTION_POINTER_UP) {
			event.type = INPUT_EVENT_POINTER_UP;
		} else {
			event.type = INPUT_EVENT_POINTER_MOVE;
		}

		//get pointer index
		event.pointerIndex = motionEvent.pointers[ptrIndex].id;

		//get pointer position
		vec2 screenWindowRatio = vec2{
			float(Screen::getWindowWidth()) / float(Screen::getWidth()),
			float(Screen::getWindowHeight()) / float(Screen::getHeight())
		};
		event.pointerPosition.x = GameActivityPointerAxes_getX(&motionEvent.pointers[ptrIndex]) / screenWindowRatio.x;
		event.pointerPosition.y = GameActivityPointerAxes_getY(&motionEvent.pointers[ptrIndex]) / screenWindowRatio.y;

		ALOG("Input : %f, %f", event.pointerPosition.x, event.pointerPosition.y);

		//return event
		return event;
	}


	//android app
	android_app* InputEvent::app = nullptr;




} // ASEngine