#ifndef __ASENGINE_EXCEPTION_H
#define __ASENGINE_EXCEPTION_H

#include <string>
#include <exception>

// inline custom exception definition
#define ASENGINE_DEFINE_EXCEPTION(exceptionName, errorMessage) \
    class exceptionName : public ASEngine::Exception           \
    {                                                          \
    public:                                                    \
        exceptionName() { m_DefaultMessage = errorMessage; }   \
        exceptionName(const std::string &message) : ASEngine::Exception(message) {} \
    }

#define ASENGINE_DEFINE_EXCEPTION_EXTEND(exceptionName, parent, errorMessage)             \
    class exceptionName : public parent                                          \
    {                                                                            \
    public:                                                                      \
        exceptionName() { m_DefaultMessage = errorMessage; }                     \
        exceptionName(const std::string& message): parent(message) {} \
    }

namespace ASEngine
{
    class Exception : public std::exception
    {
    public:
        Exception();
        Exception(const std::string& message);

        char* what();
    protected:
        std::string m_DefaultMessage = "";
    };

} // namespace ASEngine



#endif // __ASENGINE_EXCEPTION_H