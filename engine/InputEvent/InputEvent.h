//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_INPUTEVENT_H
#define ANDROIDSIMPLEENGINE_INPUTEVENT_H

#include <vector>
#include "../Math/vec2.h"
#include "../Renderer/Screen.h"

#include "../log.h"

#include <game-activity/native_app_glue/android_native_app_glue.h>

namespace ASEngine {

	enum InputEventType {
		INPUT_EVENT_POINTER_DOWN,
		INPUT_EVENT_POINTER_UP,
		INPUT_EVENT_POINTER_MOVE
	};

	class InputEvent {
	public:
		//event type
		InputEventType type;
		//pointer data
		vec2 pointerPosition;
		int pointerIndex;
		//init input
		static void init(android_app* _app);
		//pool event from queue
		static InputEvent poolEvent(int eventIndex);
	private:
		//android app
		static android_app* app;

	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_INPUTEVENT_H
