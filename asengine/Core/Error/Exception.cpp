#include "Exception.h"
#include <cstring>

namespace ASEngine
{
    Exception::Exception()
    {}

    Exception::Exception(const char* message) 
    {
        SetMessage(message);
    }

    void Exception::SetMessage(const char *message)
    {
        size_t stringSize = strlen(message) + 1;
        m_DefaultMessage = std::make_unique<char[]>(stringSize);

        memcpy(m_DefaultMessage.get(), message, stringSize);
    }

    const char *Exception::what() const noexcept
    {
        return m_DefaultMessage.get();
    }


} // namespace ASEngine
