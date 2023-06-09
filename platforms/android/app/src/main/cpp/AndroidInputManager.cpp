//
// Created by ksiks_wa3r on 5/30/23.
//

#include "AndroidInputManager.h"


AndroidInputManager::AndroidInputManager(android_app* _app) {
	app = _app;
}

//bake event
ASEngine::InputEvent AndroidInputManager::bake(int eventIndex) {
	//create event
	ASEngine::InputEvent event;

	//get event from game activity
	GameActivityMotionEvent motionEvent = app->motionEvents[eventIndex];

	int action = motionEvent.action;
	int actionMasked = action & AMOTION_EVENT_ACTION_MASK;
	int ptrIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;

	if (actionMasked == AMOTION_EVENT_ACTION_DOWN || actionMasked == AMOTION_EVENT_ACTION_POINTER_DOWN) {
		event.type = ASEngine::INPUT_EVENT_POINTER_DOWN;
	} else if (actionMasked == AMOTION_EVENT_ACTION_UP || actionMasked == AMOTION_EVENT_ACTION_POINTER_UP) {
		event.type = ASEngine::INPUT_EVENT_POINTER_UP;
	} else {
		event.type = ASEngine::INPUT_EVENT_POINTER_MOVE;
	}

	//get pointer index
	event.pointerIndex = motionEvent.pointers[ptrIndex].id;

	//get pointer position
	ASEngine::vec2 screenWindowRatio = ASEngine::vec2{
			float(ASEngine::Screen::getWindowWidth()) / float(ASEngine::Screen::getWidth()),
			float(ASEngine::Screen::getWindowHeight()) / float(ASEngine::Screen::getHeight())
	};
	event.pointerPosition.x = GameActivityPointerAxes_getX(&motionEvent.pointers[ptrIndex]) / screenWindowRatio.x;
	event.pointerPosition.y = GameActivityPointerAxes_getY(&motionEvent.pointers[ptrIndex]) / screenWindowRatio.y;

	return event;
}

void AndroidInputManager::processAndroidInput() {
	for(size_t i = 0; i < app->motionEventsCount; ++i) {
		ASEngine::InputEvent event = bake(i);
		ASEngine::Application::getSingleton()->onInputEvent(event);
	}
	android_app_clear_motion_events(app);
}