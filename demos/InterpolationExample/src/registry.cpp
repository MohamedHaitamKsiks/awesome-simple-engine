#include "ASEngine.h"
#include "InterpolationExample.h"

// module registry for the game
namespace ASEngine
{
    void Registry()
    {
        Module2D::Init();
        AudioModule::Init();

        ASENGINE_REGISTER_SYSTEM(InterpolationExample);
    }
} // ASEngine
