#include "Exception.h"

namespace ASEngine
{
    Exception::Exception()
    {};

    Exception::Exception(const std::string &message) 
    { 
        m_DefaultMessage = message; 
    };

    char * Exception::what()
    {
        return const_cast<char *>(m_DefaultMessage.c_str());
    };
} // namespace ASEngine
