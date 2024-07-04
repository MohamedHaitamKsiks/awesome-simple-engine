#ifndef __ASENGINE_ASSERT_H
#define __ASENGINE_ASSERT_H

#include "API/API.h"
#include <string>

#ifdef ASENGINE_NO_ASSERT

#define ASENGINE_ASSERT(predicat, message)

#else

#define ASENGINE_ASSERT(predicat, message) Assertion::Expect(predicat, #predicat, message, __FILE__, __LINE__)

#endif

namespace ASEngine
{
    class ASENGINE_API Assertion
    {
    public:
        static void Expect(bool predicat, const std::string& predicatMessage, const std::string& errorMessage, const std::string& filePath, int line);
    };
} // namespace ASEngine


#endif // __ASENGINE_ASSERT_H