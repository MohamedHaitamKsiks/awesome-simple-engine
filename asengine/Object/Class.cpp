#include "Class.h"
#include "Core/Debug/Debug.h"

namespace ASEngine
{
    Class::Class(UniqueString name, size_t size): m_Name(name), m_Size(size)
    {
        // Debug::Log("Register", name.GetString());
    }
} // namespace ASEngine
