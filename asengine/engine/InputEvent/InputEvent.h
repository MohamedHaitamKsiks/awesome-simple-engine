//
// Created by ksiks_wa3r on 3/27/23.
//

#ifndef ANDROIDSIMPLEENGINE_INPUTEVENT_H
#define ANDROIDSIMPLEENGINE_INPUTEVENT_H

#include "../Math/vec2.h"
#include "../Renderer/Screen.h"

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
	};

} // ASEngine

#endif //ANDROIDSIMPLEENGINE_INPUTEVENT_H
