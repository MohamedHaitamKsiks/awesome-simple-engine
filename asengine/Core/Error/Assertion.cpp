#include "Assertion.h"

#include <cstdlib>
#include "Core/Debug/Debug.h"
#include "Core/ASEngine/ASEngine.h"

namespace ASEngine
{

    void Assertion::Expect(bool predicat, const std::string &predicatMessage, const std::string &errorMessage, const std::string &filePath, int line)
    {
        if (predicat)
            return;
        
        Debug::Error(filePath, ":", line);
        Debug::Error("Assertion '", predicatMessage,"' failed");
        Debug::Error(errorMessage);
        
        ASEngine::GetInstance().Exit(1);
    }
    
} // namespace ASEngine