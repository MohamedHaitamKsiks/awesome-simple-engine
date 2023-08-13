#include "InputEvent.h"


// generate getters and setters for event fields
#define GENERATE_GETTERS_SETTERS(INPUT_TYPE) \
    template <> \
    void InputEvent::Set<INPUT_TYPE>(const INPUT_TYPE &event) \
    { \
        m_##INPUT_TYPE = event; \
        m_Type = event.Type; \
    } \
    template <> \
   INPUT_TYPE InputEvent::Get<INPUT_TYPE>() const \
    { \
        assert(m_##INPUT_TYPE.Type == m_Type); \
       return m_##INPUT_TYPE; \
    }


namespace ASEngine
{
    FOREACH(GENERATE_GETTERS_SETTERS, InputEventScreenTouch, InputEventScreenDrag, InputEventMouseButton, InputEventMouseMove, InputEventKeyboard)
} // namespace ASEngine
