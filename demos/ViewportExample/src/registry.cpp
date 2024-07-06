#include "ASEngine.h"
#include "ViewportExample.h"

// module registry for the game
void ASEngine::Registry()
{
    ASENGINE_REGISTER_SYSTEM(ViewportExample);
}