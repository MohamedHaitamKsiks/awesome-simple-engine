#ifndef __ASENGINE_EXCEPTION_H
#define __ASENGINE_EXCEPTION_H

#include <string>
#include <exception>
#include <memory>

// inline custom exception definition
#define ASENGINE_DEFINE_EXCEPTION(exceptionName, errorMessage) \
    class exceptionName : public ASEngine::Exception           \
    {                                                          \
    public:                                                    \
        ~exceptionName() {}                                    \
        exceptionName() { SetMessage(errorMessage); }   \
        exceptionName(const char* message) : ASEngine::Exception(message) {} \
    }

#define ASENGINE_DEFINE_EXCEPTION_EXTEND(exceptionName, parent, errorMessage) \
    class exceptionName : public parent                                       \
    {                                                                         \
    public:                                                                   \
        ~exceptionName() {}                                                   \
        exceptionName() { SetMessage(errorMessage); }                  \
        exceptionName(const char* message) : parent(message) {}        \
    }

namespace ASEngine
{
    class Exception : public std::exception
    {
    public:
        Exception();
        Exception(const char* message);
        virtual ~Exception() {}

        void SetMessage(const char *message);

        virtual const char* what() const noexcept override;

    protected:
        std::unique_ptr<char[]> m_DefaultMessage;
    };

} // namespace ASEngine



#endif // __ASENGINE_EXCEPTION_H