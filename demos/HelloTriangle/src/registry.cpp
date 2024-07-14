
#include "ASEngine.h"
#include "HelloTriangle.h"

// module registry for the game

namespace ASEngine
{    
    void Registry()
    {
        ASENGINE_REGISTER_SYSTEM(HelloTriangle);
    }
} // namespace ASEngine
