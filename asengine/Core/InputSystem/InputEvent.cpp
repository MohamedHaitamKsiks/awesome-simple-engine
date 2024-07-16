#include "InputEvent.h"
#include "Macros/Foreach.h"
#include "Core/Error/Assertion.h"

// generate getters and setters for event fields
#define GENERATE_GETTERS_SETTERS(INPUT_TYPE)                                      \
    template <>                                                                   \
    ASENGINE_API void InputEvent::Set<INPUT_TYPE>(const INPUT_TYPE &event)        \
    {                                                                             \
        m_##INPUT_TYPE = event;                                                   \
        m_Type = INPUT_TYPE::TYPE();                                              \
    }                                                                             \
    template <>                                                                   \
    ASENGINE_API const INPUT_TYPE &InputEvent::Get<INPUT_TYPE>() const             \
    {                                                                             \
        ASENGINE_ASSERT(INPUT_TYPE::TYPE() == m_Type, "Invalid InputEvent Type"); \
        return m_##INPUT_TYPE;                                                    \
    }

namespace ASEngine
{
    FOREACH(GENERATE_GETTERS_SETTERS, InputEventMouseButton, InputEventMouseMove, InputEventKeyboard)
} // namespace ASEngine
