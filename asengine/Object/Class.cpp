#include "Class.h"
#include "Core/Debug/Debug.h"

namespace ASEngine
{
    Class::Class(UniqueString name): m_Name(name)
    {
        Debug::Log("Register", name.GetString());
    }

} // namespace ASEngine
