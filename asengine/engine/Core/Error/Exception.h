#ifndef ASENGINE_EXCEPTION_H
#define ASENGINE_EXCEPTION_H

#include "Core/Log/Log.h"
#include <exception>

// inline custom exception definition
#define DEFINE_EXCEPTION(exceptionName, errorMessage)        \
    class exceptionName : public ASEngine::Exception         \
    {                                                        \
    public:                                                  \
        exceptionName() { m_DefaultMessage = errorMessage; } \
    }

#define DEFINE_EXCEPTION_EXTEND(exceptionName, parent, errorMessage) \
    class exceptionName : public parent                              \  
    {                                                                \
    public:                                                          \
        exceptionName() { m_DefaultMessage = errorMessage; }         \
    }

namespace ASEngine
{
    class Exception : public std::exception
    {
    public:
        Exception(const std::string& message) : m_Message(message) {};
        char* what()
        {
            return const_cast<char*>(Debug::Colorized(Debug::TextColor::RED_FG, m_Message).c_str());
        };
    private:
        std::string m_Message = "";
    };

} // namespace ASEngine



#endif // ASENGINE_EXCEPTION_H