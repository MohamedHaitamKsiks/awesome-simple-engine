#include "ASEngine.h"
#include "HelloTriangle.h"

// module registry for the game
void ASEngine::Registry()
{
    ASENGINE_REGISTER_SYSTEM(HelloTriangle);
}