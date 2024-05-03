#include "Debug.h"
#include <iostream>

namespace ASEngine
{
    void Debug::Log(const std::string &message)
    {
        std::cout << message << "\n";
    }
} // namespace ASEngine
