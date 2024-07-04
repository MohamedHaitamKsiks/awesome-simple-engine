#include "Color.h"

#include "Core/Serialization/SerializeStruct.h"

namespace ASEngine
{
    ASENGINE_SERIALIZE_STRUCT(Color, r, g, b, a)
} // namespace ASEngine
