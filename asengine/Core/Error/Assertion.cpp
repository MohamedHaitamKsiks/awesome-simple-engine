#include "Assertion.h"

#include <cstdlib>
#include "Core/Debug/Debug.h"

namespace ASEngine
{

    void Assertion::Expect(bool predicat, const std::string &predicatMessage, const std::string &errorMessage, const std::string &filePath, int line)
    {
        if (predicat)
            return;
        
        Debug::Error(filePath, ":", line);
        Debug::Error("Assertion '", predicatMessage,"' failed");
        Debug::Error(errorMessage);
        exit(1);
    }
    
} // namespace ASEngine