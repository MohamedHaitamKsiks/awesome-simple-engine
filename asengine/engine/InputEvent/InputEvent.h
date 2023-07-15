
#ifndef ASENGINE_INPUTEVENT_H
#define ASENGINE_INPUTEVENT_H

#include "engine/Math/vec2.h"
#include "engine/Renderer/Screen.h"

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

#endif //ASENGINE_INPUTEVENT_H
