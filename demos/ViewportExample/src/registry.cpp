#include "ASEngine.h"
#include "ViewportExample.h"

// module registry for the game
namespace ASEngine
{
    void Registry()
    {
        ASENGINE_REGISTER_SYSTEM(ViewportExample);
    }
} // ASEngine