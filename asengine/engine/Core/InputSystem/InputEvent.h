
#ifndef ASENGINE_INPUTEVENT_H
#define ASENGINE_INPUTEVENT_H

#include <cstdint>
#include <cassert>

#include "Macros/Foreach.h"
#include "Core/Math/vec2.h"

#include "Thirdparty/glfw3_keycodes.h"

namespace ASEngine 
{

	enum class InputEventType 
	{
		// none
		NONE = 0,
		// pointer events
		SCREEN_TOUCH,
		SCREEN_DRAG,
		// mouse event
		MOUSE_BUTTON,
		MOUSE_MOVE,
		// keyboard
		KEYBOARD
	};


	// screen input event
	struct InputEventScreenTouch
	{
		InputEventType Type = InputEventType::SCREEN_TOUCH;
		bool Pressed;
		int PointerIndex;
		vec2 Position;
	};

	// screen drag pointer event
	struct InputEventScreenDrag
	{
		InputEventType Type = InputEventType::SCREEN_DRAG;
		int PointerIndex;
		vec2 Position;
	};

	// mouse input
	enum class MouseButton
	{
		LEFT_CLICK,
		RIGHT_CLICK
	};

	// mouse input button
	struct InputEventMouseButton
	{
		InputEventType Type = InputEventType::MOUSE_BUTTON;
		MouseButton Button;
		bool Pressed;
		vec2 Position;
	};

	// mouse input move
	struct InputEventMouseMove
	{
		InputEventType Type = InputEventType::MOUSE_MOVE;
		vec2 Position;
	};

	// keycode
	using Keycode = int;

	// keyboard
	struct InputEventKeyboard
	{
		InputEventType Type = InputEventType::KEYBOARD;
		Keycode Code;
		bool Pressed;
	};

	// megaclass of all input event types so we avoid inheritance. since the number of events can't be that hight
	class InputEvent
	{
	public:
		// get event type
		inline InputEventType GetType() const
		{
			return m_Type;
		};

		// set event
		template <typename T>
		void Set(const T& event);

		// get event
		template <typename T>
		T Get() const;

	private:

		// event type
		InputEventType m_Type = InputEventType::NONE;
		// different events
		InputEventScreenTouch m_InputEventScreenTouch;
		InputEventScreenDrag m_InputEventScreenDrag;
		InputEventMouseButton m_InputEventMouseButton;
		InputEventMouseMove m_InputEventMouseMove;
		InputEventKeyboard m_InputEventKeyboard;
	};

} // ASEngine

#endif //ASENGINE_INPUTEVENT_H
