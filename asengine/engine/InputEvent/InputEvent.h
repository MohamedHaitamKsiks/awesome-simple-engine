
#ifndef ASENGINE_INPUTEVENT_H
#define ASENGINE_INPUTEVENT_H

#include "engine/Math/vec2.h"
#include "engine/Renderer/Screen.h"

namespace ASEngine {

	enum class InputEventType {
		// pointer events
		POINTER_DOWN,
		POINTER_UP,
		POINTER_MOVE
	};

	struct InputEvent {
		//event type
		InputEventType Type;
		//pointer data
		vec2 PointerPosition;
		int PointerIndex;
	};

} // ASEngine

#endif //ASENGINE_INPUTEVENT_H
