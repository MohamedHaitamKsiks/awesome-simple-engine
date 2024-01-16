#ifndef ASENGINE_EXCEPTION_H
#define ASENGINE_EXCEPTION_H

#include "Core/Log/Log.h"
#include <exception>

// inline custom exception definition
#define DEFINE_EXCEPTION(exceptionName, errorMessage)                              \
    class exceptionName : public ASEngine::Exception                               \
    {                                                                              \
    public:                                                                        \
        exceptionName() { m_DefaultMessage = errorMessage; }                       \
        exceptionName(const std::string &message) { m_DefaultMessage = message; }; \
    }

#define DEFINE_EXCEPTION_EXTEND(exceptionName, parent, errorMessage)             \
    class exceptionName : public parent                                          \
    {                                                                            \
    public:                                                                      \
        exceptionName() { m_DefaultMessage = errorMessage; }                     \
    }

namespace ASEngine
{
    class Exception : public std::exception
    {
    public:
        Exception() {};
        Exception(const std::string& message) { m_DefaultMessage = message; };
        char* what()
        {
            return const_cast<char*>(m_DefaultMessage.c_str());
        };
    protected:
        std::string m_DefaultMessage = "";
    };

} // namespace ASEngine



#endif // ASENGINE_EXCEPTION_H