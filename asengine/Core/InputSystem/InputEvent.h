
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
		// mouse event
		MOUSE_BUTTON,
		MOUSE_MOVE,
		// keyboard
		KEYBOARD,
		// gamepad
		GAMEPAD
	};


	// mouse input
	enum class MouseButton
	{
		NONE = 0,
		LEFT,
		RIGHT,
		MIDDLE
	};

	// mouse input button
	struct ASENGINE_API InputEventMouseButton
	{
		static constexpr InputEventType TYPE() 
		{
			return InputEventType::MOUSE_BUTTON;
		}
		MouseButton Button = MouseButton::NONE;
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
		InputEvent() = delete;

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
		union
		{
			InputEventMouseButton m_InputEventMouseButton;
			InputEventMouseMove m_InputEventMouseMove;
			InputEventKeyboard m_InputEventKeyboard;
		};
	};

} // ASEngine

#endif //ASENGINE_INPUTEVENT_H
