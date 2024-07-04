
#ifndef __ASENGINE_INPUTEVENT_H
#define __ASENGINE_INPUTEVENT_H

#include <cstdint>

#include "Core/Math/Vector2.h"

#include "Keycodes.h"
#include "API/API.h"

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
	struct ASENGINE_API InputEventScreenTouch
	{
		static constexpr InputEventType TYPE() 
		{
			return InputEventType::SCREEN_TOUCH;
		}
		bool Pressed;
		int PointerIndex;
		Vector2 Position;
	};

	// screen drag pointer event
	struct ASENGINE_API InputEventScreenDrag
	{
		static constexpr InputEventType TYPE()
		{ 
			return InputEventType::SCREEN_DRAG;
		}
		int PointerIndex;
		Vector2 Position;
	};

	// mouse input
	enum class MouseButton
	{
		LEFT_CLICK,
		RIGHT_CLICK
	};

	// mouse input button
	struct ASENGINE_API InputEventMouseButton
	{
		static constexpr InputEventType TYPE() 
		{
			return InputEventType::MOUSE_BUTTON;
		}
		MouseButton Button;
		bool Pressed;
		Vector2 Position;
	};

	// mouse input move
	struct ASENGINE_API InputEventMouseMove
	{
		static constexpr InputEventType TYPE() 
		{
			return InputEventType::MOUSE_MOVE;
		}
		Vector2 Position;
	};

	// keyboard
	struct ASENGINE_API InputEventKeyboard
	{
		static constexpr InputEventType TYPE()
		{
			return InputEventType::KEYBOARD;
		}
		Keycode Code;
		bool Pressed;
	};

	// megaclass of all input event types so we avoid inheritance. since the number of events can't be that hight
	class ASENGINE_API InputEvent
	{
	public:
		// get event type
		inline InputEventType GetType() const
		{
			return m_Type;
		}

		// constructors
		InputEvent() = default;

		// construct from Event
		template <typename T>
		InputEvent(const T& event)
		{
			Set(event);
		}

		// set event
		template <typename T>
		void Set(const T& event);

		// get event
		template <typename T>
		const T& Get() const;

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
